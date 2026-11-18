char * func0(char *str1,char ch,char newch)

{
  size_t sVar1;
  int i;
  char newch_local;
  char ch_local;
  char *str1_local;
  
  strcpy(func0::str2,str1);
  i = 0;
  while( true ) {
    sVar1 = strlen(func0::str2);
    if (sVar1 <= (ulong)(long)i) break;
    if (func0::str2[i] == ch) {
      func0::str2[i] = newch;
    }
    i = i + 1;
  }
  return func0::str2;
}