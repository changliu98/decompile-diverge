int hex2int(int ch)

{
  int ch_local;
  undefined4 local_c;
  
  if ((ch < 0x61) || (0x66 < ch)) {
    if ((ch < 0x41) || (0x46 < ch)) {
      local_c = ch + -0x30;
    }
    else {
      local_c = ch + -0x37;
    }
  }
  else {
    local_c = ch + -0x57;
  }
  return local_c;
}