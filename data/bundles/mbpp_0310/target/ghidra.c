char * func0(char *str1,char *result)

{
  size_t sVar1;
  ushort **ppuVar2;
  int i;
  int j;
  char *result_local;
  char *str1_local;
  
  j = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(str1);
    if (sVar1 <= (ulong)(long)i) break;
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)str1[i]] & 0x2000) == 0) {
      result[j] = str1[i];
      j = j + 1;
    }
    i = i + 1;
  }
  result[j] = '\0';
  return result;
}