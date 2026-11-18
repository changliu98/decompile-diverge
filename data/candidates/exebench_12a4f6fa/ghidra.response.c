void putoct(char *str,unsigned_short val)

{
  int iVar1;
  char local_24;
  char *cp;
  unsigned_short val_local;
  char *str_local;
  
  str[7] = '\0';
  str[6] = ' ';
  str[5] = ((byte)val & 7) + 0x30;
  cp = str + 5;
  val_local = val;
  while (cp != str) {
    iVar1 = (int)(uint)val_local >> 3;
    val_local = (unsigned_short)iVar1;
    if (iVar1 == 0) {
      local_24 = ' ';
    }
    else {
      local_24 = ((byte)iVar1 & 7) + 0x30;
    }
    cp[-1] = local_24;
    cp = cp + -1;
  }
  return;
}