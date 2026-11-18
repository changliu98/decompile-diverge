void index2xy(int index, int width, int *x, int *y)
{
  *x = index % width;
  *y = index / width;
}