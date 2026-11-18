int mv78xx0_mbus_win_cfg_offset(int win)
{
  if (win < 8)
    return (win * 16);
  return (win - 8 + 8 * 256);
}