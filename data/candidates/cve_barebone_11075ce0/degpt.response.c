char * isis_print_id(uint8_t *cp,int id_len)

{
  size_t sVar1;
  char *pcVar2;
  char *pos;
  int i;
  int id_len_local;
  uint8_t *cp_local;
  
  pos = isis_print_id::id;
  cp_local = cp;
  for (i = 1; i < 7; i = i + 1) {
    snprintf(pos,0x15 - (long)(pos + -0x1040a0),"%02x",(ulong)*cp_local);
    sVar1 = strlen(pos);
    pcVar2 = pos + sVar1;
    if ((i == 2) || (pos = pcVar2, i == 4)) {
      pos = pcVar2 + 1;
      *pcVar2 = '.';
    }
    cp_local = cp_local + 1;
  }
  if (6 < id_len) {
    snprintf(pos,0x15 - (long)(pos + -0x1040a0),".%02x",(ulong)*cp_local);
    sVar1 = strlen(pos);
    pos = pos + sVar1;
    cp_local = cp_local + 1;
  }
  if (id_len == 8) {
    snprintf(pos,0x15 - (long)(pos + -0x1040a0),"-%02x",(ulong)*cp_local);
  }
  return isis_print_id::id;
}