void reverse(char *s)

{
  char cVar1;
  char temp;
  char *end;
  char *s_local;
  
  end = s;
  if (s != (char *)0x0) {
    for (; s_local = s, *end != '\0'; end = end + 1) {
    }
    while (end = end + -1, s_local < end) {
      cVar1 = *end;
      *end = *s_local;
      *s_local = cVar1;
      s_local = s_local + 1;
    }
  }
  return;
}