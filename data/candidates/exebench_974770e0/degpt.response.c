char * envstring(char *str)

{
  char *s;
  char *str_local;
  
  s = str;
  do {
    if (*s == '\0') {
      return str;
    }
    if (*s == '-') {
      *s = '_';
    }
    else if ((*s < 'a') || ('z' < *s)) {
      if ((*s < 'A') || ('Z' < *s)) {
        *str = '\0';
        return str;
      }
    }
    else {
      *s = *s + -0x20;
    }
    s = s + 1;
  } while( true );
}