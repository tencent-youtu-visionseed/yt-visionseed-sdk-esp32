/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.2 at Mon Jun 15 20:08:30 2020. */

#ifndef PB_YTMSG_PB_H_INCLUDED
#define PB_YTMSG_PB_H_INCLUDED
#include <pb.h>

#include "CameraExposureParams.pb.h"

#include "FlasherParams.pb.h"

#include "FaceDetectionResult.pb.h"

#include "SystemStatusResult.pb.h"

#include "FileListResult.pb.h"

#include "FilePart.pb.h"

#include "RegisterFaceIdWithPicParams.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _YtRpc_Function {
    YtRpc_Function_setModel = 0,
    YtRpc_Function_getDeviceInfo = 1,
    YtRpc_Function_upgradeFirmware = 2,
    YtRpc_Function_reboot = 3,
    YtRpc_Function_getLastError = 4,
    YtRpc_Function_setExposure = 10,
    YtRpc_Function_setFlasher = 11,
    YtRpc_Function_setMainCamera = 12,
    YtRpc_Function_setCameraRotation = 13,
    YtRpc_Function_listFile = 20,
    YtRpc_Function_uploadFile = 21,
    YtRpc_Function_deleteFile = 22,
    YtRpc_Function_formatPartition = 23,
    YtRpc_Function_getConfig = 24,
    YtRpc_Function_setConfig = 25,
    YtRpc_Function_resetConfig = 26,
    YtRpc_Function_downloadFile = 27,
    YtRpc_Function_takeRawPicture = 40,
    YtRpc_Function_setDebugDrawing = 41,
    YtRpc_Function_getFaceLibInfo = 51,
    YtRpc_Function_clearFaceLib = 52,
    YtRpc_Function_registerFaceIdWithPic = 53,
    YtRpc_Function_registerFaceIdFromCamera = 54,
    YtRpc_Function_deleteFaceId = 55,
    YtRpc_Function_setFaceId = 56,
    YtRpc_Function_getFacePic = 57,
    YtRpc_Function_listFaceId = 58,
    YtRpc_Function_deleteFaceName = 59,
    YtRpc_Function_getTracePic = 60,
    YtRpc_Function_registerFaceIdWithTraceId = 61
} YtRpc_Function;
#define _YtRpc_Function_MIN YtRpc_Function_setModel
#define _YtRpc_Function_MAX YtRpc_Function_registerFaceIdWithTraceId
#define _YtRpc_Function_ARRAYSIZE ((YtRpc_Function)(YtRpc_Function_registerFaceIdWithTraceId+1))

typedef enum _YtRpcResponse_ReturnCode {
    YtRpcResponse_ReturnCode_SUCC = 0,
    YtRpcResponse_ReturnCode_CONTINUE = 1,
    YtRpcResponse_ReturnCode_ERROR_OTHER = 2,
    YtRpcResponse_ReturnCode_ERROR_CRC = 3,
    YtRpcResponse_ReturnCode_ERROR_PARAMETERS = 4,
    YtRpcResponse_ReturnCode_ERROR_RPC_TIMEOUT = 5,
    YtRpcResponse_ReturnCode_ERROR_NOT_EXIST = 6,
    YtRpcResponse_ReturnCode_ERROR_INVALID_PATH = 20,
    YtRpcResponse_ReturnCode_ERROR_FILE_EXCEED_LIMITS = 21,
    YtRpcResponse_ReturnCode_ERROR_PERMISSION = 22,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_NO_FACE_DETECTED = 50,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_TOO_MANY_FACES = 51,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_FILE_NOT_READABLE = 52,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_LIB_FULL = 53,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_TIMEOUT = 54,
    YtRpcResponse_ReturnCode_ERROR_REGISTER_FACEID_FACE_QUALITY_TOO_LOW = 56,
    YtRpcResponse_ReturnCode_ERROR_FACEID_NOT_EXIST = 55
} YtRpcResponse_ReturnCode;
#define _YtRpcResponse_ReturnCode_MIN YtRpcResponse_ReturnCode_SUCC
#define _YtRpcResponse_ReturnCode_MAX YtRpcResponse_ReturnCode_ERROR_FACEID_NOT_EXIST
#define _YtRpcResponse_ReturnCode_ARRAYSIZE ((YtRpcResponse_ReturnCode)(YtRpcResponse_ReturnCode_ERROR_FACEID_NOT_EXIST+1))

/* Struct definitions */
typedef struct _ResultDataNG {
    pb_callback_t key;
    pb_callback_t values;
/* @@protoc_insertion_point(struct:ResultDataNG) */
} ResultDataNG;

typedef struct _YtResult {
    bool has_frameId;
    uint64_t frameId;
    bool has_frameTimestampUs;
    uint64_t frameTimestampUs;
    pb_size_t which_data;
    union {
        FaceDetectionResult faceDetectionResult;
        SystemStatusResult systemStatusResult;
        char *msgOutput;
    } data;
    pb_bytes_array_t *dataV2;
/* @@protoc_insertion_point(struct:YtResult) */
} YtResult;

typedef struct _YtRpc {
    YtRpc_Function func;
    bool has_sequenceId;
    int32_t sequenceId;
    pb_size_t which_params;
    union {
        char strParams[255];
        int32_t intParams;
        CameraExposureParams cameraExposureParams;
        FlasherParams flasherParams;
        FilePart filePart;
        RegisterFaceIdWithPicParams registerFaceIdWithPicParams;
        RegisterFaceIdFromCameraParams registerFaceIdFromCameraParams;
        SetFaceIdParams setFaceIdParams;
        ListFaceIdParams listFaceIdParams;
        RegisterFaceIdWithTraceIdParams registerFaceIdWithTraceIdParams;
    } params;
    bool has_auth;
    char auth[65];
/* @@protoc_insertion_point(struct:YtRpc) */
} YtRpc;

typedef struct _YtRpcResponse {
    bool has_sequenceId;
    int32_t sequenceId;
    YtRpcResponse_ReturnCode code;
    pb_size_t which_data;
    union {
        char *strData;
        int32_t intData;
        FileListResult fileListResult;
        FilePart filePart;
        FaceIdListData faceIdListData;
    } data;
/* @@protoc_insertion_point(struct:YtRpcResponse) */
} YtRpcResponse;

typedef struct _YtMsg {
    pb_size_t which_values;
    union {
        YtRpc rpc;
        YtRpcResponse response;
        YtResult result;
    } values;
/* @@protoc_insertion_point(struct:YtMsg) */
} YtMsg;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ResultDataNG_init_default                {{{NULL}, NULL}, {{NULL}, NULL}}
#define YtResult_init_default                    {false, 0, false, 0, 0, {FaceDetectionResult_init_default}, NULL}
#define YtRpc_init_default                       {_YtRpc_Function_MIN, false, 0, 0, {""}, false, ""}
#define YtRpcResponse_init_default               {false, 0, _YtRpcResponse_ReturnCode_MIN, 0, {NULL}}
#define YtMsg_init_default                       {0, {YtRpc_init_default}}
#define ResultDataNG_init_zero                   {{{NULL}, NULL}, {{NULL}, NULL}}
#define YtResult_init_zero                       {false, 0, false, 0, 0, {FaceDetectionResult_init_zero}, NULL}
#define YtRpc_init_zero                          {_YtRpc_Function_MIN, false, 0, 0, {""}, false, ""}
#define YtRpcResponse_init_zero                  {false, 0, _YtRpcResponse_ReturnCode_MIN, 0, {NULL}}
#define YtMsg_init_zero                          {0, {YtRpc_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define ResultDataNG_key_tag                     1
#define ResultDataNG_values_tag                  2
#define YtResult_faceDetectionResult_tag         3
#define YtResult_systemStatusResult_tag          4
#define YtResult_msgOutput_tag                   5
#define YtResult_frameId_tag                     1
#define YtResult_frameTimestampUs_tag            2
#define YtResult_dataV2_tag                      101
#define YtRpc_strParams_tag                      3
#define YtRpc_intParams_tag                      4
#define YtRpc_cameraExposureParams_tag           10
#define YtRpc_flasherParams_tag                  11
#define YtRpc_filePart_tag                       21
#define YtRpc_registerFaceIdWithPicParams_tag    53
#define YtRpc_registerFaceIdFromCameraParams_tag 54
#define YtRpc_setFaceIdParams_tag                55
#define YtRpc_listFaceIdParams_tag               56
#define YtRpc_registerFaceIdWithTraceIdParams_tag 57
#define YtRpc_func_tag                           1
#define YtRpc_sequenceId_tag                     2
#define YtRpc_auth_tag                           100
#define YtRpcResponse_strData_tag                3
#define YtRpcResponse_intData_tag                4
#define YtRpcResponse_fileListResult_tag         20
#define YtRpcResponse_filePart_tag               40
#define YtRpcResponse_faceIdListData_tag         50
#define YtRpcResponse_sequenceId_tag             1
#define YtRpcResponse_code_tag                   2
#define YtMsg_rpc_tag                            1
#define YtMsg_response_tag                       2
#define YtMsg_result_tag                         3

/* Struct field encoding specification for nanopb */
extern const pb_field_t ResultDataNG_fields[3];
extern const pb_field_t YtResult_fields[7];
extern const pb_field_t YtRpc_fields[14];
extern const pb_field_t YtRpcResponse_fields[8];
extern const pb_field_t YtMsg_fields[4];

/* Maximum encoded size of messages (where known) */
/* ResultDataNG_size depends on runtime parameters */
/* YtResult_size depends on runtime parameters */
#define YtRpc_size                               (86 + sizeof(union{char f0[296]; char f21[FilePart_size];}))
/* YtRpcResponse_size depends on runtime parameters */
/* YtMsg_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define YTMSG_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
