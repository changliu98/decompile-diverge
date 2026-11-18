int str_linecount(char *str,int linelen,int *x)

{
  int lines;
  int *x_local;
  int linelen_local;
  char *str_local;
  
  lines = 1;
  for (str_local = str; *str_local != '\0'; str_local = str_local + 1) {
    if (*str_local == '\n') {
      lines = lines + 1;
      *x = 0;
    }
    else {
      *x = *x + 1;
      if (linelen <= *x) {
        lines = lines + 1;
        *x = 0;
      }
    }
  }
  return lines;
}