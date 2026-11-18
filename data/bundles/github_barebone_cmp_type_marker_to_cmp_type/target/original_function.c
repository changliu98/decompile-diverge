static bool type_marker_to_cmp_type(uint8_t type_marker, uint8_t *cmp_type) {
  if (type_marker <= 0x7F) {
    *cmp_type = CMP_TYPE_POSITIVE_FIXNUM;
    return true;
  }

  if (type_marker <= 0x8F) {
    *cmp_type = CMP_TYPE_FIXMAP;
    return true;
  }

  if (type_marker <= 0x9F) {
    *cmp_type = CMP_TYPE_FIXARRAY;
    return true;
  }

  if (type_marker <= 0xBF) {
    *cmp_type = CMP_TYPE_FIXSTR;
    return true;
  }

  if (type_marker >= 0xE0) {
    *cmp_type = CMP_TYPE_NEGATIVE_FIXNUM;
    return true;
  }

  switch (type_marker) {
    case NIL_MARKER:
      *cmp_type = CMP_TYPE_NIL;
      return true;
    case FALSE_MARKER:
      *cmp_type = CMP_TYPE_BOOLEAN;
      return true;
    case TRUE_MARKER:
      *cmp_type = CMP_TYPE_BOOLEAN;
      return true;
    case BIN8_MARKER:
      *cmp_type = CMP_TYPE_BIN8;
      return true;
    case BIN16_MARKER:
      *cmp_type = CMP_TYPE_BIN16;
      return true;
    case BIN32_MARKER:
      *cmp_type = CMP_TYPE_BIN32;
      return true;
    case EXT8_MARKER:
      *cmp_type = CMP_TYPE_EXT8;
      return true;
    case EXT16_MARKER:
      *cmp_type = CMP_TYPE_EXT16;
      return true;
    case EXT32_MARKER:
      *cmp_type = CMP_TYPE_EXT32;
      return true;
    case FLOAT_MARKER:
      *cmp_type = CMP_TYPE_FLOAT;
      return true;
    case DOUBLE_MARKER:
      *cmp_type = CMP_TYPE_DOUBLE;
      return true;
    case U8_MARKER:
      *cmp_type = CMP_TYPE_UINT8;
      return true;
    case U16_MARKER:
      *cmp_type = CMP_TYPE_UINT16;
      return true;
    case U32_MARKER:
      *cmp_type = CMP_TYPE_UINT32;
      return true;
    case U64_MARKER:
      *cmp_type = CMP_TYPE_UINT64;
      return true;
    case S8_MARKER:
      *cmp_type = CMP_TYPE_SINT8;
      return true;
    case S16_MARKER:
      *cmp_type = CMP_TYPE_SINT16;
      return true;
    case S32_MARKER:
      *cmp_type = CMP_TYPE_SINT32;
      return true;
    case S64_MARKER:
      *cmp_type = CMP_TYPE_SINT64;
      return true;
    case FIXEXT1_MARKER:
      *cmp_type = CMP_TYPE_FIXEXT1;
      return true;
    case FIXEXT2_MARKER:
      *cmp_type = CMP_TYPE_FIXEXT2;
      return true;
    case FIXEXT4_MARKER:
      *cmp_type = CMP_TYPE_FIXEXT4;
      return true;
    case FIXEXT8_MARKER:
      *cmp_type = CMP_TYPE_FIXEXT8;
      return true;
    case FIXEXT16_MARKER:
      *cmp_type = CMP_TYPE_FIXEXT16;
      return true;
    case STR8_MARKER:
      *cmp_type = CMP_TYPE_STR8;
      return true;
    case STR16_MARKER:
      *cmp_type = CMP_TYPE_STR16;
      return true;
    case STR32_MARKER:
      *cmp_type = CMP_TYPE_STR32;
      return true;
    case ARRAY16_MARKER:
      *cmp_type = CMP_TYPE_ARRAY16;
      return true;
    case ARRAY32_MARKER:
      *cmp_type = CMP_TYPE_ARRAY32;
      return true;
    case MAP16_MARKER:
      *cmp_type = CMP_TYPE_MAP16;
      return true;
    case MAP32_MARKER:
      *cmp_type = CMP_TYPE_MAP32;
      return true;
    default:
      return false;
  }
}