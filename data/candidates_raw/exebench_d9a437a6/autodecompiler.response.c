static size_t _print_sep(int flags, int depth, size_t ret)
{
 if (flags & (1 << 1))
  ret++;
 return ret;
}