drflac_bool32 drflac__seek_subframe(drflac_bs *bs,drflac_frame *frame,int subframeIndex)

{
  drflac_bool32 dVar1;
  uint bitsToSeek_2;
  drflac_uint8 lpcPrecision;
  uint bitsToSeek_1;
  uint bitsToSeek;
  drflac_uint32 subframeBitsPerSample;
  drflac_subframe *pSubframe;
  int subframeIndex_local;
  drflac_frame *frame_local;
  drflac_bs *bs_local;
  drflac_bool32 local_c;
  
  subframeIndex_local = subframeIndex;
  frame_local = frame;
  bs_local = bs;
  if (bs == (drflac_bs *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("bs != ((void*)0)","func.c",0x1547,
                  "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)");
  }
  if (frame == (drflac_frame *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("frame != ((void*)0)","func.c",0x1548,
                  "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)");
  }
  pSubframe = frame->subframes + subframeIndex;
  dVar1 = drflac__read_subframe_header(bs,pSubframe);
  if (dVar1 == 0) {
    local_c = 0;
  }
  else {
    subframeBitsPerSample = (drflac_uint32)(frame_local->header).bitsPerSample;
    if ((((frame_local->header).channelAssignment == '\b') ||
        ((frame_local->header).channelAssignment == '\n')) && (subframeIndex_local == 1)) {
      subframeBitsPerSample = subframeBitsPerSample + 1;
    }
    else if (((frame_local->header).channelAssignment == '\t') && (subframeIndex_local == 0)) {
      subframeBitsPerSample = subframeBitsPerSample + 1;
    }
    if (pSubframe->wastedBitsPerSample < subframeBitsPerSample) {
      subframeBitsPerSample = subframeBitsPerSample - pSubframe->wastedBitsPerSample;
      pSubframe->pSamplesS32 = (drflac_int32 *)0x0;
      switch(pSubframe->subframeType) {
      case '\0':
        dVar1 = drflac__seek_bits(bs_local,(ulong)subframeBitsPerSample);
        if (dVar1 == 0) {
          return 0;
        }
        break;
      case '\x01':
        bitsToSeek = (frame_local->header).blockSizeInPCMFrames * subframeBitsPerSample;
        dVar1 = drflac__seek_bits(bs_local,(ulong)bitsToSeek);
        if (dVar1 == 0) {
          return 0;
        }
        break;
      default:
        return 0;
      case '\b':
        bitsToSeek_1 = pSubframe->lpcOrder * subframeBitsPerSample;
        dVar1 = drflac__seek_bits(bs_local,(ulong)bitsToSeek_1);
        if (dVar1 == 0) {
          return 0;
        }
        dVar1 = drflac__read_and_seek_residual
                          (bs_local,(uint)(frame_local->header).blockSizeInPCMFrames,
                           (uint)pSubframe->lpcOrder);
        if (dVar1 == 0) {
          return 0;
        }
        break;
      case ' ':
        dVar1 = drflac__seek_bits(bs_local,(ulong)(pSubframe->lpcOrder * subframeBitsPerSample));
        if (dVar1 == 0) {
          return 0;
        }
        dVar1 = drflac__read_uint8(bs_local,4,&lpcPrecision);
        if (dVar1 == 0) {
          return 0;
        }
        if (lpcPrecision == '\x0f') {
          return 0;
        }
        lpcPrecision = lpcPrecision + 1;
        dVar1 = drflac__seek_bits(bs_local,(ulong)((uint)pSubframe->lpcOrder * (uint)lpcPrecision +
                                                  5));
        if (dVar1 == 0) {
          return 0;
        }
        dVar1 = drflac__read_and_seek_residual
                          (bs_local,(uint)(frame_local->header).blockSizeInPCMFrames,
                           (uint)pSubframe->lpcOrder);
        if (dVar1 == 0) {
          return 0;
        }
      }
      local_c = 1;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}