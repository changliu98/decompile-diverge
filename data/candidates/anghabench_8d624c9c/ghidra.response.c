int toup(int c)

{
  int local_10;
  int c_local;
  
  local_10 = c;
  if ((0x60 < c) && (c < 0x7b)) {
    local_10 = c + -0x20;
  }
  return local_10;
}