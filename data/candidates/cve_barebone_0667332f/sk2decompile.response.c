int bracketed_paste(PasteType type, int skip, GArray *ga) {
  char buf[80 + 1];
  int len = 0;
  char *termcode = find_termcode("bracketed-paste");
  int ret = -1;
  int save_bracketed_paste = bracketed_paste_mode;
  int save_paste = paste_mode;
  int c;
  if (termcode != NULL && strlen(termcode) > 80) termcode = NULL;
  bracketed_paste_level++;
  bracketed_paste_mode = 0;
  if (!paste_mode) set_option_value("paste", 1, NULL, 0);
  while (termcode != NULL || vpeekc() != '\0') {
    do {
      c = vgetc();
    } while (c == 0x1001 || c == 0x1002 || c == 0x1003);
    if (c == '\0' || eof_input || (interrupt_char > 0 && c == '\003')) break;
    if (mb_char_mode)
      len += mb_char2bytes(c, buf + len);
    else
      buf[len++] = c;
    buf[len] = '\0';
    if (termcode != NULL && !strncmp(buf, termcode, len)) {
      if (termcode[len] == '\0') break;
    } else {
      if (!skip) {
        switch (type) {
          case PasteType_Insert:
            if (stop_arrow() == 1) {
              c = buf[0];
              if (len == 1 && (c == '\r' || c == '\n'))
                ins_eol(c);
              else {
                ins_char_bytes(buf, len);
                AppendToRedobuffLit(buf, len);
              }
            }
            break;
          case PasteType_Replace:
            put_on_cmdline(buf, len, 1);
            break;
          case PasteType_Append:
            if (ga != NULL && ga_grow(ga, len) == 1) {
              memmove((char *)ga->data + ga->len, buf, len);
              ga->len += len;
            }
            break;
          case PasteType_Return:
            if (ret == -1) {
              if (mb_char_mode)
                ret = mb_ptr2char(buf);
              else
                ret = buf[0];
            }
            break;
        }
      }
      len = 0;
    }
  }
  bracketed_paste_level--;
  bracketed_paste_mode = save_bracketed_paste;
  if (!save_paste) set_option_value("paste", 0, NULL, 0);
  return ret;
}