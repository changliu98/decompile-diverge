static size_t do_csum(int flags, int depth, size_t ret)
{
 if (flags & (1 << 1))
  ret++;
 return ret;
}