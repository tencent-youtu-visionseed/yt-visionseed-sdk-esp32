/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 at Mon Jun 15 20:08:30 2020. */

#include "FilePart.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t FilePart_fields[5] = {
    PB_FIELD(  1, STRING  , REQUIRED, POINTER , FIRST, FilePart, path, path, 0),
    PB_FIELD(  2, INT32   , REQUIRED, STATIC  , OTHER, FilePart, totalLength, path, 0),
    PB_FIELD(  3, INT32   , REQUIRED, STATIC  , OTHER, FilePart, offset, totalLength, 0),
    PB_FIELD(  4, BYTES   , REQUIRED, POINTER , OTHER, FilePart, data, offset, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */
