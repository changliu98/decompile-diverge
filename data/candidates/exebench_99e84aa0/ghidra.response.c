char * _xtoa(unsigned_long v,char *string,int r,int is_neg)

{
  char *pcVar1;
  char *pcVar2;
  char *p;
  char buf [33];
  char *start;
  int is_neg_local;
  int r_local;
  char *string_local;
  unsigned_long v_local;
  
  pcVar1 = buf;
  v_local = v;
  do {
    p = pcVar1;
    pcVar1 = p + 1;
    *p = "0123456789abcdef"[v_local % (ulong)(long)r & 0xf];
    v_local = v_local / (ulong)(long)r;
  } while (v_local != 0);
  string_local = string;
  if (is_neg != 0) {
    *pcVar1 = '-';
    pcVar1 = p + 2;
  }
  do {
    p = pcVar1;
    pcVar2 = string_local + 1;
    *string_local = p[-1];
    pcVar1 = p + -1;
    string_local = pcVar2;
  } while (buf != p + -1);
  *pcVar2 = '\0';
  return string;
}