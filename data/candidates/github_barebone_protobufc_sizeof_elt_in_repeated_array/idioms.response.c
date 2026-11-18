static inline long sizeof_elt_in_repeated_array(enum ProtobufCType type) {
  long size;
  switch (type) {
    case PROTOBUF_C_TYPE_INT32:
    case PROTOBUF_C_TYPE_SINT32:
    case PROTOBUF_C_TYPE_SFIXED32:
    case PROTOBUF_C_TYPE_UINT32:
    case PROTOBUF_C_TYPE_FIXED32:
    case PROTOBUF_C_TYPE_FLOAT:
    case PROTOBUF_C_TYPE_ENUM:
      size = sizeof(int);
      break;
    case PROTOBUF_C_TYPE_INT64:
    case PROTOBUF_C_TYPE_SINT64:
    case PROTOBUF_C_TYPE_SFIXED64:
    case PROTOBUF_C_TYPE_UINT64:
    case PROTOBUF_C_TYPE_FIXED64:
    case PROTOBUF_C_TYPE_DOUBLE:
      size = sizeof(long);
      break;
    case PROTOBUF_C_TYPE_BOOL:
      size = sizeof(int);
      break;
    case PROTOBUF_C_TYPE_STRING:
    case PROTOBUF_C_TYPE_MESSAGE:
      size = sizeof(void *);
      break;
    case PROTOBUF_C_TYPE_BYTES:
      size = sizeof(void *) * 2;
      break;
  }
  return size;
}