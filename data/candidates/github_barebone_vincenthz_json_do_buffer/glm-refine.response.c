int __cdecl do_buffer(json_parser *parser)
{
  int ret = 0;

  // Check if parser->type is in the range [5, 11]
  if (parser->type >= 5 && parser->type <= 11)
  {
    ret = do_callback_withbuf(parser, parser->type);
    if (ret)
      return ret;
  }

  parser->buffer_offset = 0;
  return ret;
}