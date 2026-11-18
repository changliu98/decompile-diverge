drflac_bool32 __cdecl drflac_oggbs__seek_physical(drflac_oggbs *oggbs, drflac_uint64 offset, drflac_seek_origin origin)
{
  drflac_uint64 offseta; // [rsp+8h] [rbp-18h]

  offseta = offset;
  if ( origin )
  {
    while ( offseta > 0x7FFFFFFF )
    {
      if ( !oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR) )
        return 0;
      oggbs->currentBytePos += 0x7FFFFFFFLL;
      offseta -= 0x7FFFFFFFLL;
    }
    if ( oggbs->onSeek(oggbs->pUserData, offseta, DRFLAC_SEEK_CUR) )
    {
      oggbs->currentBytePos += offseta;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else if ( offset > 0x7FFFFFFF )
  {
    if ( oggbs->onSeek(oggbs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET) )
    {
      oggbs->currentBytePos = offset;
      return drflac_oggbs__seek_physical(oggbs, offset - 0x7FFFFFFF, DRFLAC_SEEK_CUR);
    }
    else
    {
      return 0;
    }
  }
  else if ( oggbs->onSeek(oggbs->pUserData, offset, DRFLAC_SEEK_SET) )
  {
    oggbs->currentBytePos = offset;
    return 1;
  }
  else
  {
    return 0;
  }
}