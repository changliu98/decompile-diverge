int func0(int size, int nblock, int nthread)
{
  int block_size = size / nblock;
  int remainder = size % nblock;
  if (remainder < nthread)
    return (block_size * nthread);
  else
    return (block_size * nblock);
}