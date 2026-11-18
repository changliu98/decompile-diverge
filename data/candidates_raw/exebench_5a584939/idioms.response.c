int set_cfg_flag(int *cfg_flag, int flag)
{
  *cfg_flag &= ~0xe;
  *cfg_flag |= (flag & 0xe);
  return *cfg_flag;
}