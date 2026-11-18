int is_valid_ref_char(char ch)

{
  int iVar1;
  char ch_local;
  int local_c;
  
  if ((byte)ch < 0x21) {
    local_c = 0;
  }
  else {
    iVar1 = (int)ch;
    if ((((iVar1 == 0x2a) || (iVar1 == 0x3a)) || (iVar1 == 0x3f)) ||
       (((iVar1 - 0x5bU < 2 || (iVar1 == 0x5e)) || (iVar1 == 0x7e)))) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}