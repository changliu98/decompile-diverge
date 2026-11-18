int __cdecl is_special_type(int type)
{
  bool v2; // [rsp+1h] [rbp-5h]

  v2 = 1;
  if ( (type & 0xF) != SNDRV_SFNT_PAT_TYPE_GUS )
    return (type & 0xF) == SNDRV_SFNT_PAT_TYPE_MAP;
  return v2;
}