int __cdecl path_source_set(int *cfg_flag, int value)
{
  *cfg_flag &= 0xFFFFFFF1;
  *cfg_flag |= value & 0xE;
  return *cfg_flag;
}