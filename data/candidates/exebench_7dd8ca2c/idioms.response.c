void hex_to_word(char *two_chars, char hex)
{
  int i;
  if (two_chars == ((void *)0))
    return;
  two_chars[0] = (hex & 0xf0) >> 4;
  two_chars[1] = (hex & 0x0f);
  for (i = 0; i < 2; i++)
    two_chars[i] = (two_chars[i] > 9 ? two_chars[i] + 'A' - 10 : two_chars[i] + '0');
}