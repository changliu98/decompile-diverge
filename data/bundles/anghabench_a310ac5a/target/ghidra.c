int is_special_type(int type)

{
  bool local_d;
  int type_local;
  
  local_d = (type & 0xfU) == SNDRV_SFNT_PAT_TYPE_GUS || (type & 0xfU) == SNDRV_SFNT_PAT_TYPE_MAP;
  return (int)local_d;
}