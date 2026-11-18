drflac_bool32 __cdecl drflac__seek_subframe(drflac_bs *bs, drflac_frame *frame, int subframeIndex)
{
  drflac_uint8 lpcPrecision; // [rsp+1Bh] [rbp-35h] BYREF
  unsigned int bitsToSeek_0; // [rsp+1Ch] [rbp-34h]
  drflac_uint32 subframeBitsPerSample; // [rsp+24h] [rbp-2Ch]
  drflac_subframe *pSubframe; // [rsp+28h] [rbp-28h]
  int subframeIndexa; // [rsp+34h] [rbp-1Ch]
  drflac_frame *framea; // [rsp+38h] [rbp-18h]
  drflac_bs *bsa; // [rsp+40h] [rbp-10h]
  drflac_bool32 v11; // [rsp+4Ch] [rbp-4h]

  bsa = bs;
  framea = frame;
  subframeIndexa = subframeIndex;
  if ( !bs )
    _assert_fail(
      "bs != ((void*)0)",
      "func.c",
      0x1547u,
      "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)");
  if ( !framea )
    _assert_fail(
      "frame != ((void*)0)",
      "func.c",
      0x1548u,
      "drflac_bool32 drflac__seek_subframe(drflac_bs *, drflac_frame *, int)");
  pSubframe = &framea->subframes[subframeIndexa];
  if ( !drflac__read_subframe_header(bsa, pSubframe) )
    return 0;
  subframeBitsPerSample = framea->header.bitsPerSample;
  if ( (framea->header.channelAssignment == 8 || framea->header.channelAssignment == 10) && subframeIndexa == 1 )
  {
    ++subframeBitsPerSample;
  }
  else if ( framea->header.channelAssignment == 9 && !subframeIndexa )
  {
    ++subframeBitsPerSample;
  }
  if ( pSubframe->wastedBitsPerSample >= subframeBitsPerSample )
    return 0;
  subframeBitsPerSample -= pSubframe->wastedBitsPerSample;
  pSubframe->pSamplesS32 = 0LL;
  switch ( pSubframe->subframeType )
  {
    case 0u:
      if ( drflac__seek_bits(bsa, subframeBitsPerSample) )
        goto LABEL_40;
      v11 = 0;
      break;
    case 1u:
      if ( drflac__seek_bits(bsa, subframeBitsPerSample * framea->header.blockSizeInPCMFrames) )
        goto LABEL_40;
      v11 = 0;
      break;
    case 8u:
      bitsToSeek_0 = subframeBitsPerSample * pSubframe->lpcOrder;
      if ( drflac__seek_bits(bsa, bitsToSeek_0) )
      {
        if ( drflac__read_and_seek_residual(bsa, framea->header.blockSizeInPCMFrames, pSubframe->lpcOrder) )
          goto LABEL_40;
        v11 = 0;
      }
      else
      {
        v11 = 0;
      }
      break;
    case 0x20u:
      if ( drflac__seek_bits(bsa, subframeBitsPerSample * pSubframe->lpcOrder) )
      {
        if ( drflac__read_uint8(bsa, 4u, &lpcPrecision) )
        {
          if ( lpcPrecision == 15 )
          {
            v11 = 0;
          }
          else if ( drflac__seek_bits(bsa, ++lpcPrecision * (unsigned int)pSubframe->lpcOrder + 5) )
          {
            if ( drflac__read_and_seek_residual(bsa, framea->header.blockSizeInPCMFrames, pSubframe->lpcOrder) )
LABEL_40:
              v11 = 1;
            else
              v11 = 0;
          }
          else
          {
            v11 = 0;
          }
        }
        else
        {
          v11 = 0;
        }
      }
      else
      {
        v11 = 0;
      }
      break;
    default:
      v11 = 0;
      break;
  }
  return v11;
}