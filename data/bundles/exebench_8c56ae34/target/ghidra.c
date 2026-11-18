void Reverse(char *s)

{
  char cVar1;
  int iVar2;
  char temp;
  int j;
  int i;
  char *s_local;
  
  j = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
  }
  iVar2 = i + -1;
  if (s[i + -1] == '\n') {
    iVar2 = i + -2;
  }
  for (; i = iVar2, j < i; j = j + 1) {
    cVar1 = s[j];
    s[j] = s[i];
    s[i] = cVar1;
    iVar2 = i + -1;
  }
  return;
}