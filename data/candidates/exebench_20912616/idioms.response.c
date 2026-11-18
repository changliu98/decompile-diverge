int dupfd(int from, int *to)
{
  if (from == -1) {
    *to = -1;
    return 1;
  }
  *to = dup(from);
  if (*to == -1)
    return 0;
  return 1;
}