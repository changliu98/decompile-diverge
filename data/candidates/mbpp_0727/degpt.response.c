char * func0(char *S)

{
  size_t sVar1;
  ushort **ppuVar2;
  int i;
  int j;
  char *S_local;
  
  j = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(S);
    if (sVar1 <= (ulong)(long)i) break;
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)S[i]] & 8) != 0) {
      func0::result[j] = S[i];
      j = j + 1;
    }
    i = i + 1;
  }
  func0::result[j] = '\0';
  return func0::result;
}