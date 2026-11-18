char *is_right(int x1, int y1, int x2, int y2, int x3, int y3)
{
  int result = (y1 - y2) * x3 + (y3 - y1) * x2 + (y2 - y3) * x1;
  if (result < 0)
    return "right";
  else
    return "not right";
}