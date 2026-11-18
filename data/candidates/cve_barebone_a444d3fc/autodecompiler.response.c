static BOOL
gdi_Bitmap_Decompress(RDPCLIENT * This, wBitmap * bitmap, BYTE * data, UINT16 width, UINT16 height, UINT16 Bpp, UINT16 size, BOOL compressed)
{
 BOOL ret;
 UINT32 src_size = size;
 GDI *gdi = This->gdi;

 bitmap->compression = 0;
 bitmap->pixel_format = gdi->current_pixel_format;
 bitmap->width = width * height;
 bitmap->height = bitmap->width * GetBytesPerPixel(bitmap->pixel_format);
 bitmap->data = (BYTE *) _aligned_malloc(bitmap->height, 16);

 if (!bitmap->data)
 {
  ret = (0);
  goto out;
 }

 if (compressed)
 {
  if (Bpp < 32)
  {
   if (!interleaved_decompress(This->rdp->interleaved, data, src_size, width, height, Bpp, bitmap->data, bitmap->pixel_format, 0, 0, 0, 0, width, height, &gdi->palette))
   {
    ret = (0);
    goto out;
   }
  }
  else
  {
   if (!planar_decompress(This->rdp->planar, data, src_size, width, height, bitmap->data, bitmap->pixel_format, width, height, 1, 0, 0, 0, 0))
   {
    ret = (0);
    goto out;
   }
  }
 }
 else
 {
  t_pixel_format src_format;
  unsigned int sbpp, dbpp;
  size_t dst_size;

  src_format = gdi_get_pixel_format(Bpp);
  sbpp = GetBytesPerPixel(src_format);
  dbpp = GetBytesPerPixel(bitmap->pixel_format);

  if ((sbpp == 0) || (dbpp == 0))
  {
   ret = (0);
   goto out;
  }

  dst_size = (src_size * dbpp) / sbpp;

  if (dst_size < bitmap->height)
  {
   ret = (0);
   goto out;
  }

  if (!freerdp_image_copy(bitmap->data, bitmap->pixel_format, 0, 0, 0, width, height, data, src_format, 0, 0, width, height, &gdi->palette, 1))
  {
   ret = (0);
   goto out;
  }
 }

 ret = (1);
out:
 return ret;
}