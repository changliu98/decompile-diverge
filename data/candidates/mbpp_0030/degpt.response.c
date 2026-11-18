int func0(char *s)

{
  int iVar1;
  size_t sVar2;
  int j;
  int i;
  int n;
  int result;
  char *s_local;
  
  result = 0;
  sVar2 = strlen(s);
  for (i = 0; i < (int)sVar2; i = i + 1) {
    for (j = 1; j <= (int)sVar2 - i; j = j + 1) {
      iVar1 = check_Equality(s,i,j);
      if (iVar1 != 0) {
        result = result + 1;
      }
    }
  }
  return result;
}