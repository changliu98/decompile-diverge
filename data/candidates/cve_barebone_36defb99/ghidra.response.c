char * gf_bt_get_next(GF_BTParser *parser,Bool point_break)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  s32 i;
  Bool go;
  u32 has_quote;
  Bool point_break_local;
  GF_BTParser *parser_local;
  
  bVar2 = true;
  gf_bt_check_line(parser);
  i = 0;
  bVar1 = false;
  do {
    while( true ) {
      if (!bVar2) goto LAB_00102780;
      if (parser->line_buffer[parser->line_pos + i] == '\"') break;
      if (!bVar1) {
        iVar3 = (int)parser->line_buffer[parser->line_pos + i];
        if ((((parser->line_buffer[parser->line_pos + i] == '\0') || (iVar3 - 9U < 2)) ||
            (iVar3 == 0xd)) || ((iVar3 == 0x20 || (iVar3 == 0x2c)))) {
LAB_001026f3:
          bVar2 = false;
        }
        else if (iVar3 == 0x2e) {
          if (point_break != GF_FALSE) {
            bVar2 = false;
          }
        }
        else if (((iVar3 == 0x5b) || (iVar3 == 0x5d)) || ((iVar3 == 0x7b || (iVar3 == 0x7d))))
        goto LAB_001026f3;
        if (!bVar2) goto LAB_00102780;
      }
      parser->cur_buffer[i] = parser->line_buffer[parser->line_pos + i];
      i = i + 1;
      if (parser->line_pos + i == parser->line_size) goto LAB_00102780;
    }
    bVar1 = !bVar1;
    parser->line_pos = parser->line_pos + 1;
  } while (parser->line_pos + i != parser->line_size);
LAB_00102780:
  parser->cur_buffer[i] = '\0';
  parser->line_pos = i + parser->line_pos;
  return parser->cur_buffer;
}