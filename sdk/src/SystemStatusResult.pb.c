/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 at Fri Apr 17 15:16:47 2020. */

#include "SystemStatusResult.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t SystemStatusResult_fields[5] = {
    PB_FIELD(  1, INT32   , REQUIRED, STATIC  , FIRST, SystemStatusResult, heartBeatId, heartBeatId, 0),
    PB_FIELD(  2, FLOAT   , REPEATED, POINTER , OTHER, SystemStatusResult, temperatures, heartBeatId, 0),
    PB_FIELD(  3, FLOAT   , REPEATED, POINTER , OTHER, SystemStatusResult, powers, temperatures, 0),
    PB_FIELD(  4, INT32   , REQUIRED, STATIC  , OTHER, SystemStatusResult, freeHeap, powers, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */
