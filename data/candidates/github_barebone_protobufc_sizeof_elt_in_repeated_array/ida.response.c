size_t __cdecl sizeof_elt_in_repeated_array(ProtobufCType type)
{
  size_t v2; // [rsp+18h] [rbp-8h]

  switch ( type )
  {
    case PROTOBUF_C_TYPE_INT32:
    case PROTOBUF_C_TYPE_SINT32:
    case PROTOBUF_C_TYPE_SFIXED32:
    case PROTOBUF_C_TYPE_UINT32:
    case PROTOBUF_C_TYPE_FIXED32:
    case PROTOBUF_C_TYPE_FLOAT:
    case PROTOBUF_C_TYPE_ENUM:
      v2 = 4LL;
      break;
    case PROTOBUF_C_TYPE_INT64:
    case PROTOBUF_C_TYPE_SINT64:
    case PROTOBUF_C_TYPE_SFIXED64:
    case PROTOBUF_C_TYPE_UINT64:
    case PROTOBUF_C_TYPE_FIXED64:
    case PROTOBUF_C_TYPE_DOUBLE:
      v2 = 8LL;
      break;
    case PROTOBUF_C_TYPE_BOOL:
      v2 = 4LL;
      break;
    case PROTOBUF_C_TYPE_STRING:
    case PROTOBUF_C_TYPE_MESSAGE:
      v2 = 8LL;
      break;
    case PROTOBUF_C_TYPE_BYTES:
      v2 = 16LL;
      break;
    default:
      _assert_fail("0", "func.c", 0x4EFu, "size_t sizeof_elt_in_repeated_array(ProtobufCType)");
  }
  return v2;
}