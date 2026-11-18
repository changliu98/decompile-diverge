int lowercase(int ch)

{
  int ch_local;
  int local_c;
  
  local_c = ch;
  if ((0x40 < ch) && (ch < 0x5b)) {
    local_c = ch + 0x20;
  }
  return local_c;
}