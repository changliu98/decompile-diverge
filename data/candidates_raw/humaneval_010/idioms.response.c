char *get_longest_palindrome(char *str)
{
  int len = strlen(str);
  char *ret = (char *)malloc((len * 2 + 1) * sizeof(char));
  if (ret == ((void *)0))
    return ((void *)0);
  int i;
  for (i = 0; i < len; i++) {
    int is_palindrome = 1;
    int j;
    for (j = 0; j < (len - i)/2; j++) {
      if (str[j + i] != str[len - 1 - j]) {
        is_palindrome = 0;
        break;
      }
    }
    if (is_palindrome) {
      strncpy(ret, str, len);
      for (j = 0; j < i; j++)
        ret[len + j] = str[i - j - 1];
      ret[len + i] = '\0';
      return ret;
    }
  }
  strncpy(ret, str, len);
  for (i = 0; i < len; i++)
    ret[len + i] = str[len - i - 1];
  ret[len * 2] = '\0';
  return ret;
}