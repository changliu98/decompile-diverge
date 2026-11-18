int get_win_id(int win)
{
  if (win < 8)
    return (win * 16);
  return (win - 8 + 8 * 256);
}