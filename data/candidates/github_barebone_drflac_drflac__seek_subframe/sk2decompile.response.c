drflac_bool32 drflac__seek_subframe(drflac_bs* bs, drflac_frame_body* frame,
                                    int subframeIndex) {
  drflac_subframe* subframe;
  unsigned int bitsToSeek;
  drflac_bool32 result;
  drflac_assert(bs != NULL);
  drflac_assert(frame != NULL);
  subframe = &frame->subframes[subframeIndex];
  if (!drflac__read_subframe_header(bs, subframe)) {
    return 0;
  }
  bitsToSeek = frame->header.subframeBits;
  if ((frame->header.blockSize == 8 || frame->header.blockSize == 10) &&
      subframeIndex == 1) {
    bitsToSeek += 1;
  } else if (frame->header.blockSize == 9 && subframeIndex == 0) {
    bitsToSeek += 1;
  }
  if (subframe->bitsRead >= bitsToSeek) {
    return 0;
  }
  bitsToSeek -= subframe->bitsRead;
  subframe->residualBuffer = NULL;
  switch (subframe->residualMethod) {
    case 0:
      result = drflac__seek_bits(bs, bitsToSeek);
      break;
    case 1:
      result = drflac__seek_bits(bs, bitsToSeek * frame->header.channels);
      break;
    case 8: {
      drflac_bool32 subframeResult;
      result = drflac__seek_bits(bs, bitsToSeek * subframe->residualBytes);
      if (result) {
        subframeResult = drflac__read_and_seek_residual(
            bs, frame->header.channels, subframe->residualBytes);
        result = subframeResult;
      }
    } break;
    case 32: {
      drflac_bool32 subframeResult;
      drflac_bool32 residualBits;
      result = drflac__seek_bits(bs, bitsToSeek * subframe->residualBytes);
      if (result) {
        result = drflac__read_uint8(bs, 4, &residualBits);
        if (result) {
          if (residualBits == 15) {
            result = 0;
          } else {
            residualBits += 1;
            result = drflac__seek_bits(
                bs, 5 + residualBits * subframe->residualBytes);
            if (result) {
              subframeResult = drflac__read_and_seek_residual(
                  bs, frame->header.channels, subframe->residualBytes);
              result = subframeResult;
            }
          }
        }
      }
    } break;
    default:
      result = 0;
      break;
  }
  return result;
}