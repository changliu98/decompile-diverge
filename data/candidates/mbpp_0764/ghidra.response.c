int func0(char *str)

{
  size_t sVar1;
  int i;
  int number_ctr;
  char *str_local;
  
  number_ctr = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(str);
    if (sVar1 <= (ulong)(long)i) break;
    if (('/' < str[i]) && (str[i] < ':')) {
      number_ctr = number_ctr + 1;
    }
    i = i + 1;
  }
  return number_ctr;
}