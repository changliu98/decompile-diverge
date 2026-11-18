char * strcpyend(char *to,char *from)

{
  char cVar1;
  char *pcVar2;
  char *from_local;
  char *to_local;
  
  from_local = from;
  pcVar2 = to;
  do {
    to_local = pcVar2;
    cVar1 = *from_local;
    *to_local = cVar1;
    from_local = from_local + 1;
    pcVar2 = to_local + 1;
  } while (cVar1 != '\0');
  return to_local;
}