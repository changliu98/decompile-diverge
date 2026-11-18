void reverse(char *s)

{
  char cVar1;
  char c;
  char *s0;
  char *s_local;
  
  for (s_local = s; s0 = s, *s_local != '\0'; s_local = s_local + 1) {
  }
  for (; s_local = s_local + -1, s0 < s_local; s0 = s0 + 1) {
    cVar1 = *s0;
    *s0 = *s_local;
    *s_local = cVar1;
  }
  return;
}