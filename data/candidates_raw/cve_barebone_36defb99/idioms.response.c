char *BT_Parser_get_word(struct _BTParser *parser, enum _Bool point_break)
{
  enum _Bool go = GF_TRUE;
  BT_Parser_get_next_line(parser);
  int i = 0;
  enum _Bool in_quote = 0;
  do
  {
    while (parser->line_buffer[parser->line_pos + i] == '\"')
    {
      in_quote = !in_quote;
      parser->line_pos++;
      if (parser->line_pos + i == parser->line_size)
        break;
    }
    if (in_quote)
      continue;
    int c = parser->line_buffer[parser->line_pos + i];
    if (c == '\0' ||
        c < 'a' ||
        c == '\r' ||
        c == ' ' ||
        c == ',')
    {
      go = GF_FALSE;
    }
    else if (c == '.' && point_break)
    {
      go = GF_FALSE;
    }
    else if (c == '[' ||
             c == ']' ||
             c == '{' ||
             c == '}')
    {
      go = GF_FALSE;
    }
    if (!go)
      break;
    parser->cur_buffer[i] = parser->line_buffer[parser->line_pos + i];
    i++;
  }
  while (parser->line_pos + i != parser->line_size);
  parser->cur_buffer[i] = '\0';
  parser->line_pos += i;
  return parser->cur_buffer;
}