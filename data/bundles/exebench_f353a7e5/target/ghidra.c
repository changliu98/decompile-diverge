void strip(char *str)

{
  int common;
  int redun;
  char *p;
  int j;
  int i;
  char *str_local;
  
  if (str == (char *)0x0) {
    return;
  }
  for (i = 1; str[i] != '\0'; i = i + 1) {
    for (j = 0; j < i; j = j + 1) {
      if (str[j] == str[i]) {
        str[i] = -1;
        break;
      }
    }
  }
  redun = 0;
  common = 0;
  i = 1;
  while( true ) {
    if (str[i] == '\0') goto LAB_001012fc;
    if (str[i] == -1) break;
    i = i + 1;
  }
  redun = i;
  for (; str[i] == -1; i = i + 1) {
  }
  common = i;
LAB_001012fc:
  if (redun == 0) {
    return;
  }
  while (str[common] != '\0') {
    if (str[common] == -1) {
      common = common + 1;
    }
    else {
      str[redun] = str[common];
      str[common] = -1;
      common = common + 1;
      redun = redun + 1;
    }
  }
  str[redun] = '\0';
  return;
}