static drmp3_bool32 drmp3__on_seek_64(drmp3 *pMP3, drmp3_uint64 frameIndex,
                                      drmp3_seek_mode seekMode) {
  if (frameIndex <= 0x7fffffff) {
    return drmp3__on_seek(pMP3, (drmp3_uint64)frameIndex, seekMode);
  }
  if (!drmp3__on_seek(pMP3, 0x7fffffff, drmp3_seek_mode_to_end)) {
    return 0;
  }
  frameIndex -= 0x7fffffff;
  while (frameIndex != 0) {
    if (frameIndex <= 0x7fffffff) {
      if (!drmp3__on_seek(pMP3, (drmp3_uint64)frameIndex,
                          drmp3_seek_mode_relative_to_end)) {
        return 0;
      }
      frameIndex = 0;
    } else {
      if (!drmp3__on_seek(pMP3, 0x7fffffff, drmp3_seek_mode_relative_to_end)) {
        return 0;
      }
      frameIndex -= 0x7fffffff;
    }
  }
  return 1;
}