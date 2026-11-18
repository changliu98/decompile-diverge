size_t
sizeof_elt_in_repeated_array(ProtobufCType type)
{
 size_t r;
 switch (type)
 {
  case PROTOBUF_C_TYPE_INT32:
  case PROTOBUF_C_TYPE_SINT32:
  case PROTOBUF_C_TYPE_SFIXED32:
  case PROTOBUF_C_TYPE_UINT32:
  case PROTOBUF_C_TYPE_FIXED32:
  case PROTOBUF_C_TYPE_FLOAT:
  case PROTOBUF_C_TYPE_ENUM:
   r = 4;
   break;
  case PROTOBUF_C_TYPE_INT64:
  case PROTOBUF_C_TYPE_SINT64:
  case PROTOBUF_C_TYPE_SFIXED64:
  case PROTOBUF_C_TYPE_UINT64:
  case PROTOBUF_C_TYPE_FIXED64:
  case PROTOBUF_C_TYPE_DOUBLE:
   r = 8;
   break;
  case PROTOBUF_C_TYPE_BOOL:
   r = 4;
   break;
  case PROTOBUF_C_TYPE_STRING:
  case PROTOBUF_C_TYPE_MESSAGE:
   r = sizeof(void *);
   break;
  case PROTOBUF_C_TYPE_BYTES:
   r = sizeof(ProtobufCBinaryData);
   break;
  default:
   do { __assert_fail("0", "func.c", 1263, "size_t sizeof_elt_in_repeated_array(ProtobufCType)"); } while(0);
 }
 return r;
}