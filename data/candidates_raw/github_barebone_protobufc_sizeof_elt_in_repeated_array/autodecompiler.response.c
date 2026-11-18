size_t
sizeof_elt_in_repeated_array (ProtobufCType type)
{
  size_t rv;
  switch ((enum ProtobufCType) (type)) {
  case PROTOBUF_C_TYPE_INT32:
  case PROTOBUF_C_TYPE_SFIXED32:
  case PROTOBUF_C_TYPE_SINT32:
  case PROTOBUF_C_TYPE_BOOL:
  case PROTOBUF_C_TYPE_ENUM:
  case PROTOBUF_C_TYPE_FIXED32:
  case PROTOBUF_C_TYPE_FLOAT:
    rv = sizeof (int32_t);
    break;
  case PROTOBUF_C_TYPE_INT64:
  case PROTOBUF_C_TYPE_SFIXED64:
  case PROTOBUF_C_TYPE_SINT64:
  case PROTOBUF_C_TYPE_FIXED64:
  case PROTOBUF_C_TYPE_DOUBLE:
    rv = sizeof (int64_t);
    break;
  case PROTOBUF_C_TYPE_BYTES:
    rv = sizeof (ProtobufCBinaryData);
    break;
  case PROTOBUF_C_TYPE_STRING:
    rv = sizeof (char *);
    break;
  case PROTOBUF_C_TYPE_MESSAGE:
    rv = sizeof (void *);
    break;
  default:
    do {___assert_fail ("0", "./func.c", 1263, "size_t sizeof_elt_in_repeated_array(ProtobufCType)");} while(0);
  }
  return rv;
}