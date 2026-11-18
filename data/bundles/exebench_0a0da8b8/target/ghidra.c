void string_reverse(char *s)

{
  char cVar1;
  int c;
  char *t;
  char *s_local;
  
  for (t = s; s_local = s, *t != '\0'; t = t + 1) {
  }
  while (s_local < t) {
    cVar1 = *s_local;
    *s_local = t[-1];
    t[-1] = cVar1;
    t = t + -1;
    s_local = s_local + 1;
  }
  return;
}