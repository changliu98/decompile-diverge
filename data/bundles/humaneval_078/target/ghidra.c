int func0(char *num)

{
  size_t sVar1;
  char *pcVar2;
  int i;
  int out;
  char *key;
  char *num_local;
  
  out = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(num);
    if (sVar1 <= (ulong)(long)i) break;
    pcVar2 = strchr("2357BD",(int)num[i]);
    if (pcVar2 != (char *)0x0) {
      out = out + 1;
    }
    i = i + 1;
  }
  return out;
}