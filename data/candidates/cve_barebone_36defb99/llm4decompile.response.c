char *gf_bt_get_next (GF_BTParser * parser, Bool point_break)
{
  u32 i;
  Bool go = ((Bool) 1);
  Bool in_string = ((Bool) 0);
  u8 cur_char;

  gf_bt_check_line (parser);

  for (i = 0; go && (parser->line_pos + i != parser->line_size); i++) {
    if (parser->line_buffer[parser->line_pos + i] == '"') {
      in_string = !in_string;
      parser->line_pos++;
      i--;
      continue;
    }

    if (!in_string) {
      cur_char = parser->line_buffer[parser->line_pos + i];
      if (cur_char == '\0' ||
          cur_char == '\r' ||
          cur_char == '\n' ||
          cur_char == ' ' ||
          cur_char == ',' ||
          (point_break != GF_FALSE && cur_char == '.') ||
          cur_char == '[' ||
          cur_char == ']' ||
          cur_char == '{' ||
          cur_char == '}') {
        go = ((Bool) 0);
      }
    }
    if (go) {
      parser->cur_buffer[i] = parser->line_buffer[parser->line_pos + i];
    }
  }
  parser->cur_buffer[i] = '\0';
  parser->line_pos += i;

  return parser->cur_buffer;
}