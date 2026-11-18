int toml_value_string(toml_unparsed_t src,char **ret,int *len)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  char *pcVar4;
  int srclen;
  int qchar;
  char *sq;
  char *sp;
  _Bool multiline;
  int *len_local;
  char **ret_local;
  toml_unparsed_t src_local;
  int local_c;
  
  multiline = false;
  *ret = (char *)0x0;
  if (src == (toml_unparsed_t)0x0) {
    local_c = -1;
  }
  else {
    cVar1 = *src;
    sVar3 = strlen(src);
    iVar2 = (int)sVar3;
    if ((cVar1 == '\'') || (cVar1 == '\"')) {
      if ((cVar1 == src[1]) && (cVar1 == src[2])) {
        multiline = true;
        sp = src + 3;
        sq = src + (long)iVar2 + -3;
        if ((((sq < sp) || (*sq != cVar1)) || (src[(long)iVar2 + -2] != cVar1)) ||
           (src[(long)iVar2 + -1] != cVar1)) {
          return -1;
        }
        if (*sp == '\n') {
          sp = src + 4;
        }
        else if ((*sp == '\r') && (src[4] == '\n')) {
          sp = src + 5;
        }
      }
      else {
        sp = src + 1;
        sq = src + (long)iVar2 + -1;
        if ((sq < sp) || (*sq != cVar1)) {
          return -1;
        }
      }
      if (cVar1 == '\'') {
        pcVar4 = norm_lit_str(sp,(int)sq - (int)sp,len,multiline,(char *)0x0,0);
        *ret = pcVar4;
      }
      else {
        pcVar4 = norm_basic_str(sp,(int)sq - (int)sp,len,multiline,(char *)0x0,0);
        *ret = pcVar4;
      }
      local_c = -1;
      if (*ret != (char *)0x0) {
        local_c = 0;
      }
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}