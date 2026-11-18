static _drflac_bool32 drflac__seek_subframe(struct _drflac_bs *bs, struct _drflac_frame *frame, int subframeIndex)
{
  struct _drflac_subframe *pSubframe;
  unsigned int subframeBitsPerSample;
  struct _drflac_subframe *pSubframe1;
  int i;
  unsigned int bitsToSeek;
  unsigned int lpcPrecision;
  ((void) sizeof ((bs != ((void *)0)) ? 1 : 0), __extension__ ({ if (bs != ((void *)0)) ; else __assert_fail ("bs != ((void *)0)", "func.c", 5999, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((frame != ((void *)0)) ? 1 : 0), __extension__ ({ if (frame != ((void *)0)) ; else __assert_fail ("frame != ((void *)0)", "func.c", 6000, __extension__ __PRETTY_FUNCTION__); }));
  pSubframe = &frame->subframes[subframeIndex];
  if ( !drflac__is_subframe_valid(bs, pSubframe) )
    return 0;
  subframeBitsPerSample = frame->header.bitsPerSample;
  if ( (frame->header.channelAssignment == 8 ||
       frame->header.channelAssignment == 10 ) &&
      subframeIndex == 1 )
    subframeBitsPerSample += 1;
  else if ( frame->header.channelAssignment == 9 &&
            subframeIndex == 0 )
    subframeBitsPerSample += 1;
  if ( pSubframe->wastedBitsPerSample >= subframeBitsPerSample )
    return 0;
  subframeBitsPerSample -= pSubframe->wastedBitsPerSample;
  pSubframe->pSamplesS32 = ((void *)0);
  switch ( pSubframe->subframeType )
  {
    case DRFLAC_SUBFRAME_TYPE_FIXED:
      if ( !drflac__bs_read(bs, subframeBitsPerSample) )
        return 0;
      break;
    case DRFLAC_SUBFRAME_TYPE_LPC:
      if ( !drflac__bs_read(bs, subframeBitsPerSample *
                                 frame->header.blockSizeInPCMFrames) )
        return 0;
      break;
    case DRFLAC_SUBFRAME_TYPE_ENTROPY:
      bitsToSeek = subframeBitsPerSample * pSubframe->lpcOrder;
      if ( !drflac__bs_read(bs, bitsToSeek) )
        return 0;
      if ( !drflac__get_subframe_samples(bs,
                                         frame->header.blockSizeInPCMFrames,
                                         pSubframe->lpcOrder ) )
        return 0;
      break;
    case DRFLAC_SUBFRAME_TYPE_ENTROPY_INDEPENDENT:
      if ( !drflac__bs_read(bs, subframeBitsPerSample *
                                 pSubframe->lpcOrder) )
        return 0;
      if ( !drflac__get_subframe_samples(bs,
                                         frame->header.blockSizeInPCMFrames,
                                         pSubframe->lpcOrder ) )
        return 0;
      break;
    default:
      return 0;
  }
  return 1;
}