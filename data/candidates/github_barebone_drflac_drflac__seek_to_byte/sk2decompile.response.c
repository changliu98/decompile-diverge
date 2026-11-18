drflac_bool32 drflac__seek_to_byte(drflac_bs* bs, drflac_uint32 byte) {
  _drflac_assert(bs != NULL);
  _drflac_assert(byte > 0);
  if (byte <= (0x7FFFFFFF)) {
    if (!bs->seek(bs->userData, byte, drflac_seek_origin_start)) {
      return 0;
    }
  } else {
    if (!bs->seek(bs->userData, 0x7FFFFFFF, drflac_seek_origin_start)) {
      return 0;
    }
    drflac_uint32 remaining = byte - 0x7FFFFFFF;
    while (remaining > 0x7FFFFFFF) {
      if (!bs->seek(bs->userData, 0x7FFFFFFF, drflac_seek_origin_current)) {
        return 0;
      }
      remaining -= 0x7FFFFFFF;
    }
    if (remaining > 0) {
      if (!bs->seek(bs->userData, remaining, drflac_seek_origin_current)) {
        return 0;
      }
    }
  }
  drflac__reset_cache(bs);
  return 1;
}