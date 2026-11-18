void swap_int(unsigned char *word)
{
  unsigned char tmp = word[0];
  word[0] = word[3];
  word[3] = tmp;
  tmp = word[1];
  word[1] = word[2];
  word[2] = tmp;
}