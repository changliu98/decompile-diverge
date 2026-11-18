int func0(char s[], char c)
{
  int i = -1;
  int length = strlen(s);
  for (int j = 0; j < length; j++) {
    if (s[j] == c) {
      i = j;
    }
  }
  if (i == -1) {
    return -1;
  }
  return i + 1;
}