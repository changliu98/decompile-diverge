static BOOL gdi_Bitmap_Decompress(rdpContext* context, GdiBitmap* bitmap,
                                  char* data, UINT16 width, UINT16 height,
                                  UINT16 bpp, UINT16 size, BOOL compressed,
                                  UINT16 format) {
  uint32 dstFormat;
  uint32 dstBytesPerPixel;
  uint32 srcBytesPerPixel;
  HRESULT hr;
  GDICONTEXT* ctx;
  ctx = context->gdi;
  bitmap->palette = 0;
  bitmap->format = ctx->server_format;
  bitmap->size = width * height * GetBytesPerPixel(bitmap->format);
  bitmap->data = (char*)aligned_malloc(bitmap->size, 16);
  if (!bitmap->data) return 0;
  if (compressed) {
    if (bpp < 32) {
      dstFormat = gdi_get_pixel_format(bpp);
      dstBytesPerPixel = GetBytesPerPixel(dstFormat);
      srcBytesPerPixel = GetBytesPerPixel(bitmap->format);
      if (dstBytesPerPixel == 0 || srcBytesPerPixel == 0) return 0;
      if (size * srcBytesPerPixel / dstBytesPerPixel < bitmap->size) return 0;
      hr = freerdp_image_copy(bitmap->data, bitmap->format, 0, 0, 0, width,
                              height, data, dstFormat, 0, 0, 0, &ctx->gdi_pal,
                              1);
      if (!hr) return 0;
    } else {
      hr = planar_decompress(context->rdpdr_server->decompress_planar, data,
                             size, width, height, bitmap->data, bitmap->format,
                             0, 0, 0, width, height, 1);
      if (!hr) return 0;
    }
  } else {
    dstFormat = gdi_get_pixel_format(bpp);
    dstBytesPerPixel = GetBytesPerPixel(dstFormat);
    srcBytesPerPixel = GetBytesPerPixel(bitmap->format);
    if (dstBytesPerPixel == 0 || srcBytesPerPixel == 0) return 0;
    if (size * srcBytesPerPixel / dstBytesPerPixel < bitmap->size) return 0;
    hr = interleaved_decompress(context->rdpdr_server->decompress_interleaved,
                                data, size, width, height, bpp, bitmap->data,
                                bitmap->format, 0, 0, 0, width, height,
                                &ctx->gdi_pal);
    if (!hr) return 0;
  }
  return 1;
}