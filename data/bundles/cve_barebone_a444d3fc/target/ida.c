BOOL __cdecl gdi_Bitmap_Decompress(
        rdpContext *context,
        rdpBitmap *bitmap,
        const BYTE *pSrcData,
        UINT32 DstWidth,
        UINT32 DstHeight,
        UINT32 bpp,
        UINT32 length,
        BOOL compressed,
        UINT32 codecId)
{
  size_t dbpp; // [rsp+58h] [rbp-68h]
  size_t sbpp; // [rsp+60h] [rbp-60h]
  UINT32 SrcFormat; // [rsp+6Ch] [rbp-54h]
  rdpGdi *gdi; // [rsp+70h] [rbp-50h]

  gdi = context->gdi;
  bitmap->compressed = 0;
  bitmap->format = gdi->dstFormat;
  bitmap->length = GetBytesPerPixel(bitmap->format) * DstHeight * DstWidth;
  bitmap->data = (BYTE *)aligned_malloc(bitmap->length, 0x10uLL);
  if ( bitmap->data )
  {
    if ( compressed )
    {
      if ( bpp >= 0x20 )
      {
        if ( !planar_decompress(
                context->codecs->planar,
                pSrcData,
                length,
                DstWidth,
                DstHeight,
                bitmap->data,
                bitmap->format,
                0,
                0,
                0,
                DstWidth,
                DstHeight,
                1) )
          return 0;
      }
      else if ( !interleaved_decompress(
                   context->codecs->interleaved,
                   pSrcData,
                   length,
                   DstWidth,
                   DstHeight,
                   bpp,
                   bitmap->data,
                   bitmap->format,
                   0,
                   0,
                   0,
                   DstWidth,
                   DstHeight,
                   &gdi->palette) )
      {
        return 0;
      }
    }
    else
    {
      SrcFormat = gdi_get_pixel_format(bpp);
      sbpp = GetBytesPerPixel(SrcFormat);
      dbpp = GetBytesPerPixel(bitmap->format);
      if ( !sbpp || !dbpp )
        return 0;
      if ( dbpp * length / sbpp < bitmap->length )
        return 0;
      if ( !freerdp_image_copy(
              bitmap->data,
              bitmap->format,
              0,
              0,
              0,
              DstWidth,
              DstHeight,
              pSrcData,
              SrcFormat,
              0,
              0,
              0,
              &gdi->palette,
              1u) )
        return 0;
    }
    return 1;
  }
  return 0;
}