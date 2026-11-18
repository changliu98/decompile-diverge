int getMax(int a, int b, int c, int *max)
{
  int choice = 1;
  int tmpMax = a;
  if (tmpMax < b) {
    tmpMax = b;
    choice = 2;
  }
  if (tmpMax < c) {
    tmpMax = c;
    choice = 3;
  }
  *max = tmpMax;
  return choice;
}