int endGB(char *s,int *addend)

{
  char *pcVar1;
  bool local_19;
  int *addend_local;
  char *s_local;
  
  *addend = 0;
  pcVar1 = strstr(s,"//");
  local_19 = true;
  if (pcVar1 == (char *)0x0) {
    pcVar1 = strstr(s,"LOCUS");
    local_19 = pcVar1 == s;
  }
  return (int)local_19;
}