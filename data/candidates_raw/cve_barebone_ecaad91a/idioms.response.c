int clear_decode(struct CLEAR_CONTEXT *clear, struct wStream *s, unsigned int subcodecByteCount, unsigned int nWidth, unsigned int nHeight, unsigned char *pDstData, unsigned int DstFormat, unsigned int nDstStep, unsigned int nXDst, unsigned int nYDst, unsigned int nDstWidth, unsigned int nDstHeight, struct gdiPalette *palette)
{
  unsigned int suboffset = 0;
  if (!read_stream("codec.clear", s, subcodecByteCount))
    return 0;
  while (suboffset < subcodecByteCount)
  {
    if (!read_stream("codec.clear", s, 13))
      return 0;
    unsigned int xStart = (UINT16)read_stream_uint32(s);
    unsigned int yStart = (UINT16)read_stream_uint32(s);
    unsigned int width = (UINT16)read_stream_uint32(s);
    unsigned int height = (UINT16)read_stream_uint32(s);
    unsigned int bitmapDataByteCount = (unsigned int)read_stream_uint64(s);
    unsigned int subcodecId = (unsigned char)read_stream_uint32(s);
    suboffset += 13;
    if (!read_stream("codec.clear", s, bitmapDataByteCount))
      return 0;
    unsigned int nXDstRel = nXDst + xStart;
    unsigned int nYDstRel = nYDst + yStart;
    if (nXDstRel + width > nWidth || nYDstRel + height > nHeight
        || xStart + width > nWidth || yStart + height > nHeight)
      return 0;
    if (!clear_set_subcontext(clear, width, height))
      return 0;
    if (subcodecId == 0)
    {
      unsigned int nSrcStep = (width * (1 << 24) + (1 << 16)) * (1 << 8);
      if (bitmapDataByteCount != (unsigned int)(height * nSrcStep))
        return 0;
      unsigned char *src = (const unsigned char *)read_stream_data(s);
      if (!clear_decode_subcontext(pDstData, nDstStep, DstFormat, nXDstRel, nYDstRel,
                                   width, height, src, nSrcStep, (1 << 24), nDstWidth, nDstHeight, palette))
        return 0;
      read_stream_skip(s, bitmapDataByteCount);
    }
    else if (subcodecId == 1)
    {
      if (!clear_decode_subcontext_rle(clear->nsc, width, height, s, bitmapDataByteCount,
                                       pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel))
        return 0;
    }
    else if (subcodecId == 2)
    {
      if (!clear_decode_subcontext_rle2(s, bitmapDataByteCount, width, height,
                                        pDstData, DstFormat, nDstStep, nXDstRel, nYDstRel, nDstWidth, nDstHeight))
        return 0;
    }
    else
      return 0;
    suboffset += (unsigned int)bitmapDataByteCount;
  }
  return 1;
}