void oct_to_word(char *three_chars, char oct)
{
  if(three_chars == NULL)
    return;
  three_chars[0] = (oct & 0300) >> 6;
  three_chars[1] = (oct & 070) >> 3;
  three_chars[2] = oct & 7;

  oct = 0;
  for(;oct < 3;oct++)
    three_chars[oct] += '0';
}