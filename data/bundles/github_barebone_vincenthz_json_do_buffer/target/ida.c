int __cdecl do_buffer(json_parser *parser)
{
  int ret; // [rsp+Ch] [rbp-14h]

  ret = 0;
  if ( (unsigned int)(parser->type - 5) <= 6 )
  {
    ret = do_callback_withbuf(parser, parser->type);
    if ( ret )
      return ret;
  }
  parser->buffer_offset = 0;
  return ret;
}