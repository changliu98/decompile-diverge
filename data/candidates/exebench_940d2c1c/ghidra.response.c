void escape(char *s1,char *s2)

{
  char cVar1;
  int j;
  int i;
  char *s2_local;
  char *s1_local;
  
  j = 0;
  for (i = 0; s2[i] != '\0'; i = i + 1) {
    cVar1 = s2[i];
    if (cVar1 == '\t') {
      s1[j] = '\\';
      s1[j + 1] = 't';
      j = j + 1;
    }
    else if (cVar1 == '\n') {
      s1[j] = '\\';
      s1[j + 1] = 'n';
      j = j + 1;
    }
    else if (cVar1 == '\"') {
      s1[j] = '\\';
      s1[j + 1] = '\"';
      j = j + 1;
    }
    else if (cVar1 == '\\') {
      s1[j] = '\\';
      s1[j + 1] = '\\';
      j = j + 1;
    }
    else {
      s1[j] = s2[i];
    }
    j = j + 1;
  }
  s1[j] = s2[i];
  return;
}