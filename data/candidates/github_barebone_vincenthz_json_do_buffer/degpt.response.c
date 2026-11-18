int do_buffer(json_parser *parser)

{
  int ret;
  json_parser *parser_local;
  int local_c;
  
  ret = 0;
  if ((6 < parser->type - JSON_INT) ||
     (ret = do_callback_withbuf(parser,parser->type), local_c = ret, ret == 0)) {
    parser->buffer_offset = 0;
    local_c = ret;
  }
  return local_c;
}