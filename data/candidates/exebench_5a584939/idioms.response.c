int path_source_set(int *cfg_flag, int flag)
{
  *cfg_flag &= ~0xe;
  *cfg_flag |= (flag & 0xe);
  return *cfg_flag;
}