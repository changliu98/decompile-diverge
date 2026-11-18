char * str_rev(char *s)

{
  char cVar1;
  char *pcVar2;
  char ch;
  char *t;
  char *h;
  char *s_local;
  
  pcVar2 = s;
  do {
    t = pcVar2;
    pcVar2 = t + 1;
    h = s;
  } while (*t != '\0');
  while (t = t + -1, h < t) {
    cVar1 = *h;
    *h = *t;
    *t = cVar1;
    h = h + 1;
  }
  return s;
}