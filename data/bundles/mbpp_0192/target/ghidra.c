int func0(char *str)

{
  bool bVar1;
  ushort **ppuVar2;
  bool local_19;
  int flag_n;
  int flag_l;
  char *str_local;
  
  local_19 = false;
  bVar1 = false;
  for (str_local = str; *str_local != '\0'; str_local = str_local + 1) {
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)(uint)(byte)*str_local] & 0x400) != 0) {
      local_19 = true;
    }
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)(uint)(byte)*str_local] & 0x800) != 0) {
      bVar1 = true;
    }
  }
  local_19 = local_19 && bVar1;
  return (int)local_19;
}