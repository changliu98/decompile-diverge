static drflac_bool32 drflac_oggbs__seek_physical(drflac_oggbs* BS,
                                                 drflac_uint64 offset,
                                                 drflac_seek_origin origin) {
  if (origin == drflac_seek_origin_start) {
    if (offset <= 0x7FFFFFFF) {
      if (!BS->onSeek(BS->pUserData, offset, drflac_seek_origin_current)) {
        return 0;
      }
      BS->currentOffset = offset;
      return 1;
    } else {
      if (!BS->onSeek(BS->pUserData, 0x7FFFFFFF, drflac_seek_origin_current)) {
        return 0;
      }
      BS->currentOffset = offset;
      return drflac_oggbs__seek_physical(BS, offset - 0x7FFFFFFF,
                                         drflac_seek_origin_end);
    }
  } else {
    while (offset > 0x7FFFFFFF) {
      if (!BS->onSeek(BS->pUserData, 0x7FFFFFFF, drflac_seek_origin_end)) {
        return 0;
      }
      BS->currentOffset += 0x7FFFFFFF;
      offset -= 0x7FFFFFFF;
    }
    if (!BS->onSeek(BS->pUserData, offset, drflac_seek_origin_end)) {
      return 0;
    }
    BS->currentOffset += offset;
    return 1;
  }
}