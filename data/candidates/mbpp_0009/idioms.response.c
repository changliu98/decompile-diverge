int func0(char *str)
{
  int i; int j;
  int len = strlen(str);
  char *min_str = (char *) ( (char *) ( (char *) ( &min_str ) - ( ( ( ( ( (char *) ( &min_str ) ) - ( (char *) 0 ) ) + ( ( sizeof(char *) * (len * 2 + 1) ) + ( sizeof(char *) - 1 ) ) & ~ ( sizeof(char *) - 1 ) ) ) ) ) );
  char *min_str_ptr = min_str;
  strcpy(min_str, str);
  strcat(min_str, str);
  for (i = 1; i <= len; i++) {
    int equal = 1;
    for (j = 0; j < len; j++) {
      if (str[j] != min_str[j + i]) {
        equal = 0;
        break;
      }
    }
    if (equal) {
      int min_len = i;
      int min_len_set = 1;
      return min_len;
    }
  }
  int min_len = len;
  int min_len_set = 1;
  return min_len;
}