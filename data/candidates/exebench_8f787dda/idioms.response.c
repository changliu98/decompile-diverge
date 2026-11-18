void index_to_xwy(int index, int width, int *x, int *y)
{
  *x = index % width;
  *y = index / width;
}