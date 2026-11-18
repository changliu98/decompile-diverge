static void nm_writel(int val, void *data)
{
  int *i = (int *)data;
  *i = val;
}