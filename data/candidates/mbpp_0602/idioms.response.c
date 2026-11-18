char func0(char *str)
{
  int length = strlen(str);
  int i;
  for (i = 0; i < length; i++) {
    int count = 0;
    int j;
    for (j = 0; j <= i; j++) {
      if (str[j] == str[i]) {
        count++;
      }
    }
    if (count > 1) {
      return str[i];
    }
  }
  return '0';
}