int json_parse(struct json_parser *parser)
{
  int ret = 0;
  switch (parser->type)
  {
    case JSO_TYPE_OBJECT:
    case JSO_TYPE_ARRAY:
    case JSO_TYPE_STRING:
    case JSO_TYPE_NUMBER:
    case JSO_TYPE_TRUE:
    case JSO_TYPE_FALSE:
    case JSO_TYPE_NULL:
      ret = json_parse_value(parser, parser->type);
      if (ret)
      {
        return ret;
      }
    default:
      break;
  }
  parser->buffer_offset = 0;
  return ret;
}