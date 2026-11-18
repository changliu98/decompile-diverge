int a2d(char ch)

{
  char ch_local;
  undefined4 local_c;
  
  if ((ch < '0') || ('9' < ch)) {
    if ((ch < 'a') || ('f' < ch)) {
      if ((ch < 'A') || ('F' < ch)) {
        local_c = -1;
      }
      else {
        local_c = ch + -0x37;
      }
    }
    else {
      local_c = ch + -0x57;
    }
  }
  else {
    local_c = ch + -0x30;
  }
  return local_c;
}