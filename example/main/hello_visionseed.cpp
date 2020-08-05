#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include <sys/time.h>


#include "YtMsgPool.h"
#include "YtVisionSeed.h"
#include "YtFaceAlignment.h"
#include "DataLinkESP32.h"

#define REG_QUALITY_THD 0.9

YtVisionSeed *visionseed;

typedef struct {
    uint32_t trace_id;
    std::string name;
    uint64_t first_seen;
    uint64_t last_seen;
    float quality;
    bool enter_event_fired;
    YtRpcResponse_ReturnCode err;
} record_t;


std::map<uint32_t, record_t> records;
std::map<uint32_t, bool> registed;

uint64_t _time()
{
    struct timeval    tv;
    struct timezone   tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void do_register(const char *prefix, record_t &record)
{
    uint64_t ts = _time();
    if (!registed[record.trace_id])
    {
        int32_t faceId = -1;
        char name[32];
        snprintf(name, sizeof(name), "%s-%d-%lld", prefix, record.trace_id, ts);
        printf("[%11s] [%d] '%s' (q:%6.3f)\n", "register", record.trace_id, name, record.quality);
        record.err = visionseed->RegisterFaceIdWithTraceId(name, record.trace_id, &faceId);
        printf("[%s%11s"COLOR_NO"] [%d] '%s' (ret:%d, faceId:%d)\n", record.err == YtRpcResponse_ReturnCode_SUCC?COLOR_GREEN:COLOR_RED, "registed", record.trace_id, name, record.err, faceId);
        if (record.err == YtRpcResponse_ReturnCode_SUCC)
        {
            registed[record.trace_id] = true;
        }
    }
}

//获取状态
void OnStatus(shared_ptr<YtMsg> message)
{
    if (VSRESULT_DATA(message).systemStatusResult.heartBeatId == 0)
    {
        printf("[%llu] VisionSeed boot done!\n", _time());
        records.clear();
        registed.clear();
    }
}
//获取识别结果
void OnResult(shared_ptr<YtMsg> message)
{
    uint64_t ts = _time();
    uint32_t count = 0;
    YtDataLink::getResult(VSRESULT_DATAV2(message)->bytes, &count, {VS_MODEL_FACE_DETECTION});
    // printf("frame: %" PRIu64 ", size: %d, count: %d, free: %d\n", VSRESULT(message).frameId, VSRESULT_DATAV2(message)->size, count, esp_get_free_heap_size());
    for (int i = 0; i < count; i ++)
    {
        YtVisionSeedResultTypeRect rect;
        YtVisionSeedResultTypeString faceName = {.conf = 0, .p = 0};
        YtVisionSeedResultTypeArray quality = {.count = 0, .p = 0};
        uint32_t trace_id;

        // 获取检测框（模型ID路径：人脸检测/index）
        if (!YtDataLink::getResult(VSRESULT_DATAV2(message)->bytes, &rect, {VS_MODEL_FACE_DETECTION, i}))
        {
            continue;
        }
        // 获取人脸识别结果（模型ID路径：人脸检测/index/人脸识别）
        if (!YtDataLink::getResult(VSRESULT_DATAV2(message)->bytes, &faceName, {VS_MODEL_FACE_DETECTION, i, VS_MODEL_FACE_RECOGNITION}))
        {
            continue;
        }
        // 获取轨迹ID（模型ID路径：人脸检测/index/轨迹）
        if (!YtDataLink::getResult(VSRESULT_DATAV2(message)->bytes, &trace_id, {VS_MODEL_FACE_DETECTION, i, VS_MODEL_DETECTION_TRACE}))
        {
            continue;
        }
        // 获取人脸质量（模型ID路径：人脸检测/index/人脸质量）
        if (!YtDataLink::getResult(VSRESULT_DATAV2(message)->bytes, &quality, {VS_MODEL_FACE_DETECTION, i, VS_MODEL_FACE_QUALITY}))
        {
            continue;
        }

        // printf("--------------\n");
        // printf("[traceId] %d\n", trace_id);
        // printf("[faceName] %s conf: %6.3f\n", faceName.p, faceName.conf);
        // printf("[rect] (%d, %d, %d, %d) cls: %d conf: %6.3f\n", rect.x, rect.y, rect.w, rect.h, rect.cls, rect.conf);
        if (records.find(trace_id) == records.end())
        {
            records[trace_id] = {trace_id, faceName.p, ts, ts, quality.p[0], false, YtRpcResponse_ReturnCode_SUCC};
            if (strlen(faceName.p) > 0)
            {
                //进入
                printf("[%s%11s"COLOR_NO"] [%d] '%s' (q:%6.3f, c:%6.3f)\n", COLOR_CYAN, "enter", trace_id, faceName.p, quality.p[0], faceName.conf);
            }
            else
            {
                //未识别出
                printf("[%s%11s"COLOR_NO"] [%d] '%s' (q:%6.3f, c:%6.3f)\n", COLOR_CYAN_LIGHT, "new", trace_id, faceName.p, quality.p[0], faceName.conf);
            }
        }
        else
        {
            if (quality.p[0] > records[trace_id].quality)
            {
                //质量更好才会更新，同VisionSeed内部逻辑
                records[trace_id].quality = quality.p[0];
                if (records[trace_id].name != faceName.p)
                {
                    printf("[%11s] [%d] '%s' -> '%s' (q:%6.3f, c:%6.3f)\n", "change", trace_id, records[trace_id].name.c_str(), faceName.p, quality.p[0], faceName.conf);
                    records[trace_id].name = faceName.p;
                }
            }
            records[trace_id].last_seen = ts;
        }
    }
}

extern "C" void app_main()
{
    visionseed = new YtVisionSeed("2~"); // uart 2, '~' means swap tx, rx pin
    //注册结果获取接口
    visionseed->RegisterOnResult(OnResult);
    visionseed->RegisterOnStatus(OnStatus);
}
