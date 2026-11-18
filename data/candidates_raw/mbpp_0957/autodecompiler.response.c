int ceillog2(int i)
{
  return((int) (log2((double) (i & (-i)))+1.0));
}