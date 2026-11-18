void escape(char *s,char *t)

{
  char cVar1;
  int iVar2;
  int j;
  int i;
  char *t_local;
  char *s_local;
  
  i = 0;
  for (j = 0; (s[i] != '\0' && (cVar1 = t[j], cVar1 != '\0')); j = j + 1) {
    if (cVar1 == '\t') {
      iVar2 = i + 1;
      s[i] = '\\';
      i = i + 2;
      s[iVar2] = 't';
    }
    else if (cVar1 == '\n') {
      s[i] = '\\';
      s[i + 1] = 'n';
      i = i + 2;
    }
    else {
      s[i] = t[j];
      i = i + 1;
    }
  }
  return;
}