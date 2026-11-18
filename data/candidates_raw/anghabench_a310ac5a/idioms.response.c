int pat_is_gus(int type)
{
  int ret = 1;
  if ((type & 0x0f) == SNDRV_SFNT_PAT_TYPE_GUS)
    ret = 1;
  else if ((type & 0x0f) == SNDRV_SFNT_PAT_TYPE_MAP)
    ret = 0;
  return (ret);
}