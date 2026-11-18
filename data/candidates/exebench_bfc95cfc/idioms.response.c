void oct_to_word(char *three_chars, char oct)
{
  char i;
  if (three_chars) {
    three_chars[0] = (oct & 0xc0) >> 6;
    three_chars[1] = (oct & 0x38) >> 3;
    three_chars[2] = (oct & 0x07);
    for (i = 0; i < 3; i++)
      three_chars[i] += '0';
  }
}