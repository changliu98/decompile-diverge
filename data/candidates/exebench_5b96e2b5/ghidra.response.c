void reverse(char *s)

{
  char cVar1;
  char tmp;
  char *t;
  char *s_local;
  
  for (t = s; s_local = s, *t != '\0'; t = t + 1) {
  }
  for (; t = t + -1, s_local < t; s_local = s_local + 1) {
    cVar1 = *s_local;
    *s_local = *t;
    *t = cVar1;
  }
  return;
}