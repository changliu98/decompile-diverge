sds sdscatrepr(sds s,char *p,size_t len)

{
  char cVar1;
  ushort **ppuVar2;
  sds pcVar3;
  size_t len_local;
  char *p_local;
  sds s_local;
  
  s_local = sdscatlen(s,&DAT_001053c8,1);
  len_local = len;
  p_local = p;
  while (len_local != 0) {
    cVar1 = *p_local;
    if (cVar1 == '\a') {
      s_local = sdscatlen(s_local,&DAT_001053d7,2);
    }
    else if (cVar1 == '\b') {
      s_local = sdscatlen(s_local,&DAT_001053da,2);
    }
    else if (cVar1 == '\t') {
      s_local = sdscatlen(s_local,&DAT_001053d4,2);
    }
    else if (cVar1 == '\n') {
      s_local = sdscatlen(s_local,&DAT_001053ce,2);
    }
    else if (cVar1 == '\r') {
      s_local = sdscatlen(s_local,&DAT_001053d1,2);
    }
    else if ((cVar1 == '\"') || (cVar1 == '\\')) {
      s_local = sdscatprintf(s_local,"\\%c",(ulong)(uint)(int)*p_local);
    }
    else {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)*p_local] & 0x4000) == 0) {
        s_local = sdscatprintf(s_local,"\\x%02x",(ulong)(byte)*p_local);
      }
      else {
        s_local = sdscatprintf(s_local,"%c",(ulong)(uint)(int)*p_local);
      }
    }
    p_local = p_local + 1;
    len_local = len_local - 1;
  }
  pcVar3 = sdscatlen(s_local,&DAT_001053c8,1);
  return pcVar3;
}