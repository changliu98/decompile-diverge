char *__cdecl gf_bt_get_next(GF_BTParser *parser, Bool point_break)
{
  int v3; // [rsp+4h] [rbp-1Ch]
  s32 i; // [rsp+8h] [rbp-18h]
  Bool go; // [rsp+Ch] [rbp-14h]
  _BOOL4 has_quote; // [rsp+10h] [rbp-10h]

  go = GF_TRUE;
  gf_bt_check_line(parser);
  i = 0;
  has_quote = 0;
  do
  {
    while ( parser->line_buffer[i + parser->line_pos] == 34 )
    {
      has_quote = !has_quote;
      ++parser->line_pos;
      if ( i + parser->line_pos == parser->line_size )
        goto LABEL_21;
    }
    if ( has_quote )
      goto LABEL_20;
    v3 = parser->line_buffer[i + parser->line_pos];
    if ( !parser->line_buffer[i + parser->line_pos] || (unsigned int)(v3 - 9) < 2 || v3 == 13 || v3 == 32 || v3 == 44 )
    {
LABEL_16:
      go = GF_FALSE;
      goto LABEL_19;
    }
    if ( v3 == 46 )
    {
      if ( point_break )
        go = GF_FALSE;
    }
    else if ( v3 == 91 || v3 == 93 || v3 == 123 || v3 == 125 )
    {
      goto LABEL_16;
    }
LABEL_19:
    if ( go == GF_FALSE )
      break;
LABEL_20:
    parser->cur_buffer[i] = parser->line_buffer[i + parser->line_pos];
    ++i;
  }
  while ( i + parser->line_pos != parser->line_size );
LABEL_21:
  parser->cur_buffer[i] = 0;
  parser->line_pos += i;
  return parser->cur_buffer;
}