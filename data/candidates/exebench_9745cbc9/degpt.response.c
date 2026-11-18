int itoa(char *str,int i)

{
  char *pcVar1;
  uint local_44;
  char *s;
  char *p;
  char *end;
  char tmp [12];
  uint u;
  int i_local;
  char *str_local;
  
  local_44 = i;
  if (i < 0) {
    local_44 = -i;
  }
  u = local_44;
  pcVar1 = tmp + 0xb;
  do {
    p = pcVar1;
    pcVar1 = p + -1;
    *p = (char)((ulong)u % 10) + '0';
    u = u / 10;
  } while (u != 0);
  s = str;
  if (i < 0) {
    *pcVar1 = '-';
    p = pcVar1;
  }
  for (; p < &u; p = p + 1) {
    *s = *p;
    s = s + 1;
  }
  *s = '\0';
  return (int)s - (int)str;
}