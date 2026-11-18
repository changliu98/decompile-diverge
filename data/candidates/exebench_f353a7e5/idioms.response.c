void strip(char *str)
{
  int i; int j;
  int redun; int common;
  if (str == ((void *)0))
    return;
  for (i = 1; str[i] != '\0'; i++) {
    for (j = 0; j < i; j++) {
      if (str[j] == str[i]) {
        str[i] = -1;
        break;
      }
    }
  }
  redun = 0;
  common = 0;
  for (i = 1; str[i] != '\0'; i++) {
    if (str[i] == -1) {
      redun = i;
      while (str[i] == -1)
        i++;
      common = i;
      break;
    }
  }
  if (redun != 0) {
    while (str[common] != '\0') {
      if (str[common] == -1)
        common++;
      else {
        str[redun++] = str[common];
        str[common++] = -1;
      }
    }
    str[redun] = '\0';
  }
}