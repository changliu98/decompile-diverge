int path_source_set(int *cfg_flag, int value)
{
    *cfg_flag &= ~0x0e;
    *cfg_flag |= value & 0x0e;
    return *cfg_flag;
}