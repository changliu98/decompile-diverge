void snake_upcase_char(char *c)

{
  char *c_local;
  
  if ((*c < 'a') || ('z' < *c)) {
    if (*c == '-') {
      *c = '_';
    }
  }
  else {
    *c = *c & 0xdf;
  }
  return;
}