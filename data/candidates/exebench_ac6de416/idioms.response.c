void adjust_mode_num(int *mode)
{
  if (*mode > 9)
    *mode = 9;
  else if (*mode < 0)
    *mode = 0;
}