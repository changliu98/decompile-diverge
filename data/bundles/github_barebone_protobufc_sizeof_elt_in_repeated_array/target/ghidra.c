size_t sizeof_elt_in_repeated_array(ProtobufCType type)

{
  ProtobufCType type_local;
  size_t local_10;
  
  switch(type) {
  case PROTOBUF_C_TYPE_INT32:
  case PROTOBUF_C_TYPE_SINT32:
  case PROTOBUF_C_TYPE_SFIXED32:
  case PROTOBUF_C_TYPE_UINT32:
  case PROTOBUF_C_TYPE_FIXED32:
  case PROTOBUF_C_TYPE_FLOAT:
  case PROTOBUF_C_TYPE_ENUM:
    local_10 = 4;
    break;
  case PROTOBUF_C_TYPE_INT64:
  case PROTOBUF_C_TYPE_SINT64:
  case PROTOBUF_C_TYPE_SFIXED64:
  case PROTOBUF_C_TYPE_UINT64:
  case PROTOBUF_C_TYPE_FIXED64:
  case PROTOBUF_C_TYPE_DOUBLE:
    local_10 = 8;
    break;
  case PROTOBUF_C_TYPE_BOOL:
    local_10 = 4;
    break;
  case PROTOBUF_C_TYPE_STRING:
  case PROTOBUF_C_TYPE_MESSAGE:
    local_10 = 8;
    break;
  case PROTOBUF_C_TYPE_BYTES:
    local_10 = 0x10;
    break;
  default:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","func.c",0x4ef,"size_t sizeof_elt_in_repeated_array(ProtobufCType)");
  }
  return local_10;
}