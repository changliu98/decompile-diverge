static int drflac_oggbs__seek_physical(struct _drflac_oggbs *self, long offset, enum _drflac_seek_origin origin)
{
  if ( origin == DRFLAC_SEEK_SET )
  {
    if ( offset > 0x7fffffff )
    {
      if ( !self->onSeek(self->pUserData, 0x7fffffff, DRFLAC_SEEK_SET) )
        return 0;
      self->currentBytePos = offset;
      return drflac_oggbs__seek_physical(self, offset - 0x7fffffff, DRFLAC_SEEK_CUR);
    }
    if ( !self->onSeek(self->pUserData, offset, DRFLAC_SEEK_SET) )
      return 0;
    self->currentBytePos = offset;
  }
  else
  {
    while ( offset > 0x7fffffff )
    {
      if ( !self->onSeek(self->pUserData, 0x7fffffff, DRFLAC_SEEK_CUR) )
        return 0;
      self->currentBytePos += 0x7fffffff;
      offset -= 0x7fffffff;
    }
    if ( !self->onSeek(self->pUserData, offset, DRFLAC_SEEK_CUR) )
      return 0;
    self->currentBytePos += offset;
  }
  return 1;
}