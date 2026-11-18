void inplace_strcpy(char *to,char *from)

{
  char *from_local;
  char *to_local;
  
  from_local = from;
  to_local = to;
  while (*from_local != '\0') {
    *to_local = *from_local;
    from_local = from_local + 1;
    to_local = to_local + 1;
  }
  *to_local = *from_local;
  return;
}