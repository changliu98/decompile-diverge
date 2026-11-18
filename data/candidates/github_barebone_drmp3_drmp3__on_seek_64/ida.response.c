drmp3_bool32 __cdecl drmp3__on_seek_64(drmp3 *pMP3, drmp3_uint64 offset, drmp3_seek_origin origin)
{
  drmp3_uint64 offseta; // [rsp+8h] [rbp-18h]

  if ( offset <= 0x7FFFFFFF )
    return drmp3__on_seek(pMP3, offset, origin);
  if ( !drmp3__on_seek(pMP3, 0x7FFFFFFF, DRMP3_SEEK_SET) )
    return 0;
  offseta = offset - 0x7FFFFFFF;
  while ( offseta )
  {
    if ( offseta > 0x7FFFFFFF )
    {
      if ( !drmp3__on_seek(pMP3, 0x7FFFFFFF, DRMP3_SEEK_CUR) )
        return 0;
      offseta -= 0x7FFFFFFFLL;
    }
    else
    {
      if ( !drmp3__on_seek(pMP3, offseta, DRMP3_SEEK_CUR) )
        return 0;
      offseta = 0LL;
    }
  }
  return 1;
}