size_t sizeof_elt_in_repeated_array(ProtobufCType protobuf_type)
{
  // Determine the size of an element in a repeated array based on its protobuf type
  switch(protobuf_type) {
  // 32-bit integer types and related types occupy 4 bytes
  case PROTOBUF_C_TYPE_INT32:
  case PROTOBUF_C_TYPE_SINT32:
  case PROTOBUF_C_TYPE_SFIXED32:
  case PROTOBUF_C_TYPE_UINT32:
  case PROTOBUF_C_TYPE_FIXED32:
  case PROTOBUF_C_TYPE_FLOAT:
  case PROTOBUF_C_TYPE_ENUM:
  case PROTOBUF_C_TYPE_BOOL:
    return 4;
  // 64-bit integer types, floating-point types, strings, and messages occupy 8 bytes
  case PROTOBUF_C_TYPE_INT64:
  case PROTOBUF_C_TYPE_SINT64:
  case PROTOBUF_C_TYPE_SFIXED64:
  case PROTOBUF_C_TYPE_UINT64:
  case PROTOBUF_C_TYPE_FIXED64:
  case PROTOBUF_C_TYPE_DOUBLE:
  case PROTOBUF_C_TYPE_STRING:
  case PROTOBUF_C_TYPE_MESSAGE:
    return 8;
  // Bytes type occupies 16 bytes (0x10)
  case PROTOBUF_C_TYPE_BYTES:
    return 0x10;
  // Default case: handle unsupported types by triggering an assertion failure
  default:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","func.c",0x4ef,"size_t sizeof_elt_in_repeated_array(ProtobufCType)");
  }
}