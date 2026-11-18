int32_t readUnicode(char *in,int *bit_no_p,int len)

{
  int iVar1;
  int32_t iVar2;
  int local_38;
  int local_34;
  int32_t count;
  int sign;
  int idx;
  int len_local;
  int *bit_no_p_local;
  char *in_local;
  int local_c;
  
  iVar1 = getStepCodeIdx(in,len,bit_no_p,5);
  if (iVar1 == 99) {
    local_c = 0x7fffff63;
  }
  else if (iVar1 == 5) {
    local_c = getStepCodeIdx(in,len,bit_no_p,4);
    local_c = local_c + 0x7fffff00;
  }
  else if (iVar1 < 0) {
    local_c = 0;
  }
  else {
    if (*bit_no_p < len) {
      local_34 = readBit(in,*bit_no_p);
    }
    else {
      local_34 = 0;
    }
    *bit_no_p = *bit_no_p + 1;
    if ((int)(*bit_no_p + (uint)"\x06\f\x0e\x10\x15"[iVar1] + -1) < len) {
      iVar2 = getNumFromBits(in,len,*bit_no_p,(uint)"\x06\f\x0e\x10\x15"[iVar1]);
      local_38 = uni_adder[iVar1] + iVar2;
      *bit_no_p = (uint)"\x06\f\x0e\x10\x15"[iVar1] + *bit_no_p;
      if (local_34 != 0) {
        local_38 = -local_38;
      }
      local_c = local_38;
    }
    else {
      local_c = 0x7fffff63;
    }
  }
  return local_c;
}