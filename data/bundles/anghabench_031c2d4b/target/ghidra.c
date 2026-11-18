bool tomoyo_invalid(uchar c)

{
  bool local_b;
  bool local_a;
  uchar c_local;
  
  local_a = false;
  if (c != '\0') {
    local_b = c < 0x21 || 0x7e < c;
    local_a = local_b;
  }
  return (bool)local_a;
}