int func0(int x, int y)
{
  int result;

  if (x > y) {
    result = -1;
  } else if (x == y && y % 2 == 1) {
    result = -1;
  } else if (y % 2 == 1) {
    result = y - 1;
  } else {
    result = y;
  }

  return result;
}