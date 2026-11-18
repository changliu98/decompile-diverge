size_t sizeof_elt_in_repeated_array(WireType wire_type) {
  switch (wire_type) {
    case WIRETYPE_VARINT:
    case WIRETYPE_FIXED32:
    case WIRETYPE_SFIXED32:
    case WIRETYPE_SINT32:
    case WIRETYPE_INT32:
    case WIRETYPE_ENUM:
      return 4;
    case WIRETYPE_FIXED64:
    case WIRETYPE_SFIXED64:
    case WIRETYPE_SINT64:
    case WIRETYPE_INT64:
    case WIRETYPE_UINT64:
    case WIRETYPE_DOUBLE:
      return 8;
    case WIRETYPE_BOOL:
      return 4;
    case WIRETYPE_BYTES:
      return 16;
    case WIRETYPE_STRING:
    case WIRETYPE_GROUP_START:
      return 8;
    default:
      _exit(0);
      return 0;
  }
}