void reverse(char *rline)

{
  char cVar1;
  int iVar2;
  char temp;
  int j;
  int i;
  char *rline_local;
  
  for (i = 0; rline[i] != '\0'; i = i + 1) {
  }
  iVar2 = i + -1;
  if (rline[i + -1] == '\n') {
    iVar2 = i + -2;
  }
  i = iVar2;
  for (j = 0; j < i; j = j + 1) {
    cVar1 = rline[j];
    rline[j] = rline[i];
    rline[i] = cVar1;
    i = i + -1;
  }
  return;
}