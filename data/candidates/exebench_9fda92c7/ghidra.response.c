void reverse(char *s)

{
  char cVar1;
  char *pcVar2;
  char buf [2];
  char *end;
  char *start;
  char *s_local;
  
  pcVar2 = s;
  do {
    end = pcVar2;
    pcVar2 = end + 1;
    start = s;
  } while (*end != '\0');
  for (; end = end + -1, start < end; start = start + 1) {
    cVar1 = *start;
    *start = *end;
    *end = cVar1;
  }
  return;
}