void adjust_mode_num(int *num)
{
 if (*num > 9)
  *num = 9;
 else if (*num < 0)
  *num = 0;
}