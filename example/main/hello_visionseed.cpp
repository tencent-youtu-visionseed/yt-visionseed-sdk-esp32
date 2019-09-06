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
void OnFaceRetrieveResult(shared_ptr<YtMsg> message)
{
    // printf("frame: %" PRIu64 ", frameTimestampUs: %" PRIu64 "\n", VSRESULT(message).frameId, VSRESULT(message).frameTimestampUs);
    uint64_t ts = _time();
    for (size_t i = 0; i < VSRESULT_DATA(message).faceDetectionResult.face_count; i++)
    {
        Face &face = VSRESULT_DATA(message).faceDetectionResult.face[i];
        if (!face.has_traceId)
        {
            LOG_E("you're running old firmware!\n");
            return;
        }

        if (records.find(face.traceId) == records.end())
        {
            records[face.traceId] = {face.traceId, face.name, ts, ts, face.quality, false, YtRpcResponse_ReturnCode_SUCC};
            if (face.has_name)
            {
                //进入
                printf("[%s%11s"COLOR_NO"] [%d] '%s' (q:%6.3f, c:%6.3f)\n", COLOR_CYAN, "enter", face.traceId, face.name, face.quality, face.nameConfidence);
            }
            else
            {
                //未识别出
                printf("[%s%11s"COLOR_NO"] [%d] '%s' (q:%6.3f, c:%6.3f)\n", COLOR_CYAN_LIGHT, "new", face.traceId, face.name, face.quality, face.nameConfidence);
            }
        }
        else
        {
            if (face.quality > records[face.traceId].quality)
            {
                //质量更好才会更新，同VisionSeed内部逻辑
                records[face.traceId].quality = face.quality;
                if (records[face.traceId].name != face.name)
                {
                    printf("[%11s] [%d] '%s' -> '%s' (q:%6.3f, c:%6.3f)\n", "change", face.traceId, records[face.traceId].name.c_str(), face.name, face.quality, face.nameConfidence);
                    records[face.traceId].name = face.name;
                }
            }
            records[face.traceId].last_seen = ts;
        }
    }
}

extern "C" void app_main()
{
    visionseed = new YtVisionSeed("2~"); // uart 2, '~' means swap tx, rx pin
    //注册结果获取接口
    visionseed->RegisterOnFaceResult(OnFaceRetrieveResult);
    visionseed->RegisterOnStatus(OnStatus);
}
