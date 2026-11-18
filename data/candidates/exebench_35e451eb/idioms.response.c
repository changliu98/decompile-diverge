void adjust_point(int *percent)
{
  if (*percent < 0)
    *percent = 0;
  else if (*percent > 100)
    *percent = 100;
}