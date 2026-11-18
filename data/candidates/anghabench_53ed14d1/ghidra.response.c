uint mv78xx0_mbus_win_cfg_offset(int win)

{
  int win_local;
  undefined4 local_c;
  
  if (win < 8) {
    local_c = win << 4;
  }
  else {
    local_c = (win + -8) * 0x10 + 0x900;
  }
  return local_c;
}