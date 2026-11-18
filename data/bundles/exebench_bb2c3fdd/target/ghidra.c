void reverse(char *s)

{
  char cVar1;
  char c;
  int i;
  char *p;
  int length;
  char *s_local;
  
  length = 0;
  for (p = s; *p != '\0'; p = p + 1) {
    length = length + 1;
  }
  for (i = 0; i <= length / 2 + -1; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[((long)length + -1) - (long)i];
    s[((long)length + -1) - (long)i] = cVar1;
  }
  return;
}