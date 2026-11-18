char * string_copy(char *dest,char *a)

{
  char *d;
  char *s;
  char *a_local;
  char *dest_local;
  char *local_10;
  
  if ((a == (char *)0x0) || (d = dest, s = a, dest == (char *)0x0)) {
    local_10 = (char *)0x0;
  }
  else {
    while (*s != '\0') {
      *d = *s;
      d = d + 1;
      s = s + 1;
    }
    *d = '\0';
    local_10 = dest;
  }
  return local_10;
}