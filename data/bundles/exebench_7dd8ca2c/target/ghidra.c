void hex_to_word(char *two_chars,char hex)

{
  char hex_local;
  char *two_chars_local;
  
  if (two_chars != (char *)0x0) {
    *two_chars = (char)((int)((int)hex & 0xf0U) >> 4);
    two_chars[1] = hex & 0xf;
    for (hex_local = '\0'; hex_local < '\x02'; hex_local = hex_local + '\x01') {
      if (two_chars[hex_local] < '\n') {
        two_chars[hex_local] = two_chars[hex_local] + '0';
      }
      else {
        two_chars[hex_local] = two_chars[hex_local] + '7';
      }
    }
  }
  return;
}