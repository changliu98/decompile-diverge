size_t utf8StrWidth(char *str, size_t len)
{
 size_t i, width;
 size_t char_len;
 int chr;

 width = 0;
 i = 0;
 bool after_zwj = false;
 while (true) {
  if (i >= len)
   break;

  chr = utf8DecodeChar(&str[i], &char_len);
  if (chr == 27) {
   ssize_t esc_len = ansiEscapeLen(&str[i], len - i);

   if (esc_len > 0) {
    i += esc_len;
    continue;
   }
  }

  if (after_zwj)
   after_zwj = false;
  else
   width += utf8CharWidth(chr);

  if (isZWJ(chr))
   after_zwj = true;

  i += char_len;
 }

 return width;
}