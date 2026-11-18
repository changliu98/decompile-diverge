BOOL
resize_vbar_entry(CLEAR_CONTEXT* clear, CLEAR_VBAR_ENTRY* vBarEntry)
{
  UINT32 bpp;
  UINT32 oldSize;
  UINT32 newSize;
  UINT32 diffSize;
  UINT8* pixels;

  if (vBarEntry->size < vBarEntry->count)
  {
    bpp = FreeRDPGetBytesPerPixel(clear->format);
    oldSize = vBarEntry->size * bpp;
    newSize = vBarEntry->count * bpp;
    diffSize = newSize - oldSize;
    vBarEntry->size = vBarEntry->count;
    pixels = (UINT8*)winpr_aligned_recalloc(vBarEntry->pixels, vBarEntry->size, bpp, 32);

    if (pixels == NULL)
      return 0;

    memset(pixels + oldSize, 0, diffSize);
    vBarEntry->pixels = pixels;
  }

  if ((vBarEntry->pixels == NULL) && (vBarEntry->size != 0))
    return 0;

  return 1;
}