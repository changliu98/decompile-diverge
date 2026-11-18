int path_source_set(int *cfg_flag,int value)

{
  int value_local;
  int *cfg_flag_local;
  
  *cfg_flag = *cfg_flag & 0xfffffff1;
  *cfg_flag = value & 0xeU | *cfg_flag;
  return *cfg_flag;
}