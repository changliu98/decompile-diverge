BINN_PRIVATE int type_family(int type)  {

  switch (type) {
    case BINN_LIST:
    case BINN_MAP:
    case BINN_OBJECT:
      return BINN_FAMILY_BINN;

    case BINN_INT8:
    case BINN_INT16:
    case BINN_INT32:
    case BINN_INT64:
    case BINN_UINT8:
    case BINN_UINT16:
    case BINN_UINT32:
    case BINN_UINT64:
      return BINN_FAMILY_INT;

    case BINN_FLOAT32:
    case BINN_FLOAT64:
    //case BINN_SINGLE:
    case BINN_SINGLE_STR:
    //case BINN_DOUBLE:
    case BINN_DOUBLE_STR:
      return BINN_FAMILY_FLOAT;

    case BINN_STRING:
    case BINN_HTML:
    case BINN_CSS:
    case BINN_XML:
    case BINN_JSON:
    case BINN_JAVASCRIPT:
      return BINN_FAMILY_STRING;

    case BINN_BLOB:
    case BINN_JPEG:
    case BINN_GIF:
    case BINN_PNG:
    case BINN_BMP:
      return BINN_FAMILY_BLOB;

    case BINN_DECIMAL:
    case BINN_CURRENCY:
    case BINN_DATE:
    case BINN_TIME:
    case BINN_DATETIME:
      return BINN_FAMILY_STRING;

    case BINN_BOOL:
      return BINN_FAMILY_BOOL;

    case BINN_NULL:
      return BINN_FAMILY_NULL;

    default:
      // if it wasn't found
      return BINN_FAMILY_NONE;
  }

}