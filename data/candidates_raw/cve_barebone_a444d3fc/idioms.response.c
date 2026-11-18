int rdp_decode(struct rdpContext *context, struct rdpBitmap *bitmap, unsigned char *pSrcData, unsigned int DstWidth, unsigned int DstHeight, unsigned int bpp, unsigned int length, int compressed, int codecId)
{
 struct rdpGdi *gdi = context->gdi;
 unsigned int srcFormat;
 unsigned int dstFormat;
 unsigned long srcBpp;
 unsigned long dstBpp;
 bitmap->compressed = 0;
 bitmap->format = gdi->dstFormat;
 bitmap->length = rdp_get_bytes_per_line(bitmap->format)*DstWidth*DstHeight;
 bitmap->data = (unsigned char *)aligned_malloc(bitmap->length, 16);
 if (bitmap->data == ((void *)0))
  return 0;
 if (compressed)
 {
  if (bpp < 32)
  {
   if (!context->codecs->interleaved->decode(context->codecs->interleaved,
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
    &gdi->palette))
    return 0;
  }
  else
  {
   if (!context->codecs->planar->decode(context->codecs->planar,
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
    1))
    return 0;
  }
 }
 else
 {
  srcFormat = rdp_get_src_format(bpp);
  srcBpp = rdp_get_bits_per_pixel(srcFormat);
  dstBpp = rdp_get_bits_per_pixel(bitmap->format);
  if (srcBpp == 0 || dstBpp == 0)
   return 0;
  if (dstBpp*length/srcBpp < bitmap->length)
   return 0;
  if (!rdp_convert(bitmap->data, bitmap->format,
    0,
    0,
    0,
    DstWidth,
    DstHeight,
    pSrcData,
    srcFormat,
    0,
    0,
    0,
    &gdi->palette,
    1))
   return 0;
 }
 return 1;
}