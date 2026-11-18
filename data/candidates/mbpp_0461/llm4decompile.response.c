int func0(char *str)
{
  int upper_ctr;
  size_t len;

  upper_ctr = 0;
  len = strlen(str);
  if (len > 0) {
    if (str[0] >= 'A' && str[0] <= 'Z') {
      upper_ctr = 1;
    }
  }
  return upper_ctr;
}