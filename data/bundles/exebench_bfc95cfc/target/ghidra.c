void oct_to_word(char *three_chars,char oct)

{
  char oct_local;
  char *three_chars_local;
  
  if (three_chars != (char *)0x0) {
    *three_chars = (char)((int)((int)oct & 0xc0U) >> 6);
    three_chars[1] = (char)(oct & 0x38U) >> 3;
    three_chars[2] = oct & 7;
    for (oct_local = '\0'; oct_local < '\x03'; oct_local = oct_local + '\x01') {
      three_chars[oct_local] = three_chars[oct_local] + '0';
    }
  }
  return;
}