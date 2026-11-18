int is_special_type(int type_code)
{
  return (int)((type_code & 0xfU) == SNDRV_SFNT_PAT_TYPE_GUS || (type_code & 0xfU) == SNDRV_SFNT_PAT_TYPE_MAP);
}