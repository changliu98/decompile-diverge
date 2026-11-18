void func3(int direction, int *pos)
{
  if (direction > 0)
    *pos += 1;
  else
    *pos -= 1;
}