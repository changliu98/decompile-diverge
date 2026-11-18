int str_to_int(char *str,int *num)

{
  int digit;
  int r;
  int i;
  int *num_local;
  char *str_local;
  int local_c;
  
  i = 0;
  r = 10;
  *num = 0;
  if ((*str == '0') && (str[1] == 'x')) {
    i = 2;
    r = 0x10;
  }
  if (str[i] == '\0') {
    local_c = -1;
  }
  else {
    for (; str[i] != '\0'; i = i + 1) {
      if ((str[i] < '0') || ('9' < str[i])) {
        if ((r == 0x10) && (('@' < str[i] && (str[i] < 'G')))) {
          digit = str[i] + -0x37;
        }
        else {
          if ((r != 0x10) || ((str[i] < 'a' || ('f' < str[i])))) {
            return -1;
          }
          digit = str[i] + -0x57;
        }
      }
      else {
        digit = str[i] + -0x30;
      }
      *num = *num * r + digit;
    }
    local_c = 0;
  }
  return local_c;
}