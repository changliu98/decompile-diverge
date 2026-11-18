size_t __cdecl sizeof_elt_in_repeated_array(ProtobufCType type)
{
  switch ( type )
  {
    case PROTOBUF_C_TYPE_INT32:
    case PROTOBUF_C_TYPE_SINT32:
    case PROTOBUF_C_TYPE_SFIXED32:
    case PROTOBUF_C_TYPE_UINT32:
    case PROTOBUF_C_TYPE_FIXED32:
    case PROTOBUF_C_TYPE_FLOAT:
    case PROTOBUF_C_TYPE_ENUM:
    case PROTOBUF_C_TYPE_BOOL:
      return 4;
    case PROTOBUF_C_TYPE_INT64:
    case PROTOBUF_C_TYPE_SINT64:
    case PROTOBUF_C_TYPE_SFIXED64:
    case PROTOBUF_C_TYPE_UINT64:
    case PROTOBUF_C_TYPE_FIXED64:
    case PROTOBUF_C_TYPE_DOUBLE:
    case PROTOBUF_C_TYPE_STRING:
    case PROTOBUF_C_TYPE_MESSAGE:
      return 8;
    case PROTOBUF_C_TYPE_BYTES:
      return 16;
    default:
      _assert_fail("0", "func.c", 0x4EFu, "size_t sizeof_elt_in_repeated_array(ProtobufCType)");
      return 0; // Fallback return to satisfy compiler, though _assert_fail typically aborts
  }
}