int drmp3__on_seek_64(struct _drmp3 *pMP3, long offset, int origin)
{
  if (offset < 0x80000000)
    return drmp3_seek_int(pMP3, (unsigned int)offset, origin);
  if (drmp3_seek_int(pMP3, 0x7fffffff, DRMP3_SEEK_SET) == 0)
    return 0;
  offset -= 0x7fffffff;
  while (offset > 0)
  {
    if (offset < 0x80000000)
    {
      if (drmp3_seek_int(pMP3, (unsigned int)offset, DRMP3_SEEK_CUR) == 0)
        return 0;
      offset = 0;
    }
    else
    {
      if (drmp3_seek_int(pMP3, 0x7fffffff, DRMP3_SEEK_CUR) == 0)
        return 0;
      offset -= 0x7fffffff;
    }
  }
  return 1;
}