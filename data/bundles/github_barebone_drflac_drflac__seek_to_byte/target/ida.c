drflac_bool32 __cdecl drflac__seek_to_byte(drflac_bs *bs, drflac_uint64 offsetFromStart)
{
  drflac_uint64 bytesRemaining; // [rsp+0h] [rbp-20h]

  if ( !bs )
    _assert_fail("bs != ((void*)0)", "func.c", 0xB41u, "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
  if ( !offsetFromStart )
    _assert_fail(
      "offsetFromStart > 0",
      "func.c",
      0xB42u,
      "drflac_bool32 drflac__seek_to_byte(drflac_bs *, drflac_uint64)");
  if ( offsetFromStart <= 0x7FFFFFFF )
  {
    if ( !bs->onSeek(bs->pUserData, offsetFromStart, DRFLAC_SEEK_SET) )
      return 0;
    goto LABEL_19;
  }
  if ( bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_SET) )
  {
    for ( bytesRemaining = offsetFromStart - 0x7FFFFFFF; bytesRemaining > 0x7FFFFFFF; bytesRemaining -= 0x7FFFFFFFLL )
    {
      if ( !bs->onSeek(bs->pUserData, 0x7FFFFFFF, DRFLAC_SEEK_CUR) )
        return 0;
    }
    if ( bytesRemaining && !bs->onSeek(bs->pUserData, bytesRemaining, DRFLAC_SEEK_CUR) )
      return 0;
LABEL_19:
    drflac__reset_cache(bs);
    return 1;
  }
  return 0;
}