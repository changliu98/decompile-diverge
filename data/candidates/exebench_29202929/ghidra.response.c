char * mystpcpy(char *to,char *from)

{
  char cVar1;
  char *from_local;
  char *to_local;
  
  to_local = to;
  for (from_local = from; cVar1 = *from_local, *to_local = cVar1, cVar1 != '\0';
      from_local = from_local + 1) {
    to_local = to_local + 1;
  }
  return to_local;
}