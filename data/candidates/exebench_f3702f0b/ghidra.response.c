void escape(char *s,char *t)

{
  char cVar1;
  int iVar2;
  int j;
  int i;
  char *t_local;
  char *s_local;
  
  j = 0;
  for (i = 0; t[i] != '\0'; i = i + 1) {
    cVar1 = t[i];
    if (cVar1 == '\t') {
      iVar2 = j + 1;
      s[j] = '\\';
      j = j + 2;
      s[iVar2] = 't';
    }
    else if (cVar1 == '\n') {
      iVar2 = j + 1;
      s[j] = '\\';
      j = j + 2;
      s[iVar2] = 'n';
    }
    else if (cVar1 == ' ') {
      s[j] = '\\';
      s[j + 1] = 'b';
      j = j + 2;
    }
    else {
      s[j] = t[i];
      j = j + 1;
    }
  }
  s[j] = '\0';
  return;
}