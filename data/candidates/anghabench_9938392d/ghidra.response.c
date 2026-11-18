int Q_islower(int c)

{
  int c_local;
  undefined4 local_c;
  
  if ((c < 0x61) || (0x7a < c)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}