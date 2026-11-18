BOOL __cdecl clear_decompress_subcodecs_data(
        CLEAR_CONTEXT *clear,
        wStream *s,
        UINT32 subcodecByteCount,
        UINT32 nWidth,
        UINT32 nHeight,
        BYTE *pDstData,
        UINT32 DstFormat,
        UINT32 nDstStep,
        UINT32 nXDst,
        UINT32 nYDst,
        UINT32 nDstWidth,
        UINT32 nDstHeight,
        const gdiPalette *palette)
{
  const BYTE *src; // r14
  UINT32 nSrcStep; // [rsp+68h] [rbp-68h]
  UINT32 nYDstRel; // [rsp+6Ch] [rbp-64h]
  UINT32 nXDstRel; // [rsp+70h] [rbp-60h]
  UINT8 subcodecId; // [rsp+77h] [rbp-59h]
  UINT32 bitmapDataByteCount; // [rsp+78h] [rbp-58h]
  UINT16 height; // [rsp+7Ch] [rbp-54h]
  UINT16 width; // [rsp+7Eh] [rbp-52h]
  UINT16 yStart; // [rsp+80h] [rbp-50h]
  UINT16 xStart; // [rsp+82h] [rbp-4Eh]
  UINT32 suboffset; // [rsp+84h] [rbp-4Ch]
  UINT32 suboffseta; // [rsp+84h] [rbp-4Ch]

  suboffset = 0;
  if ( !Stream_CheckAndLogRequiredLength("codec.clear", s, subcodecByteCount) )
    return 0;
  while ( suboffset < subcodecByteCount )
  {
    if ( !Stream_CheckAndLogRequiredLength("codec.clear", s, 0xDuLL) )
      return 0;
    xStart = Stream_Get_UINT16(s);
    yStart = Stream_Get_UINT16(s);
    width = Stream_Get_UINT16(s);
    height = Stream_Get_UINT16(s);
    bitmapDataByteCount = Stream_Get_UINT32(s);
    subcodecId = Stream_Get_UINT8(s);
    suboffseta = suboffset + 13;
    if ( !Stream_CheckAndLogRequiredLength("codec.clear", s, bitmapDataByteCount) )
      return 0;
    nXDstRel = xStart + nXDst;
    nYDstRel = yStart + nYDst;
    if ( width + (unsigned __int64)nXDstRel > nWidth )
      return 0;
    if ( height + (unsigned __int64)nYDstRel > nHeight )
      return 0;
    if ( width + (unsigned __int64)xStart > nWidth )
      return 0;
    if ( height + (unsigned __int64)yStart > nHeight )
      return 0;
    if ( !clear_resize_buffer(clear, width, height) )
      return 0;
    if ( subcodecId )
    {
      if ( subcodecId == 1 )
      {
        if ( !clear_decompress_nscodec(
                clear->nsc,
                width,
                height,
                s,
                bitmapDataByteCount,
                pDstData,
                DstFormat,
                nDstStep,
                nXDstRel,
                nYDstRel) )
          return 0;
      }
      else
      {
        if ( subcodecId != 2 )
          return 0;
        if ( !clear_decompress_subcode_rlex(
                s,
                bitmapDataByteCount,
                width,
                height,
                pDstData,
                DstFormat,
                nDstStep,
                nXDstRel,
                nYDstRel,
                nDstWidth,
                nDstHeight) )
          return 0;
      }
    }
    else
    {
      nSrcStep = FreeRDPGetBytesPerPixel(0x18020888u) * width;
      if ( bitmapDataByteCount != height * (unsigned __int64)nSrcStep )
        return 0;
      src = (const BYTE *)Stream_Pointer(s);
      if ( !convert_color(
              pDstData,
              nDstStep,
              DstFormat,
              nXDstRel,
              nYDstRel,
              width,
              height,
              src,
              nSrcStep,
              0x18020888u,
              nDstWidth,
              nDstHeight,
              palette) )
        return 0;
      Stream_Seek(s, bitmapDataByteCount);
    }
    suboffset = suboffseta + bitmapDataByteCount;
  }
  return 1;
}