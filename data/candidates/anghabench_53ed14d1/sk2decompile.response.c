static int mv78xx0_mbus_win_cfg_offset(int win) {
  if (win < 8)
    return win * 16;
  else
    return 0x900 + (win - 8) * 16;
}