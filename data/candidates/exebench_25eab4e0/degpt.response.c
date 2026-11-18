int substitute(char *data,char from,char to)

{
  char *pcVar1;
  char *c;
  char to_local;
  char from_local;
  char *data_local;
  
  c = data;
  while( true ) {
    pcVar1 = strchr(c,(int)from);
    if (pcVar1 == (char *)0x0) break;
    c = pcVar1 + 1;
    *pcVar1 = to;
  }
  return 1;
}