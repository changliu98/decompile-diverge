void reverse(char *s)

{
  char cVar1;
  bool bVar2;
  char tmp;
  int j;
  int i;
  char *s_local;
  
  i = 0;
  while( true ) {
    j = i;
    bVar2 = false;
    if (s[i] != '\0') {
      bVar2 = s[i] != '\n';
    }
    if (!bVar2) break;
    i = i + 1;
  }
  for (i = 0; j = j + -1, i < j; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[j];
    s[j] = cVar1;
  }
  return;
}