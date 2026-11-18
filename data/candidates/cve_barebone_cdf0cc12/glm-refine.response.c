BITMAP_UPDATE *__cdecl update_read_bitmap_update(rdpUpdate *update, wStream *s)
{
  BITMAP_DATA *newdata;
  UINT16 count;
  BITMAP_UPDATE *bitmapUpdate;
  UINT32 i;

  // Allocate the BITMAP_UPDATE structure (size 0x18 = 24 bytes)
  bitmapUpdate = (BITMAP_UPDATE *)calloc(1uLL, 0x18uLL);
  
  // Fail if allocation failed or stream has less than 2 bytes remaining
  if (!bitmapUpdate || Stream_GetRemainingLength(s) < 2)
    goto fail;

  // Read 16-bit little-endian integer from stream
  bitmapUpdate->number = (unsigned __int16)(s->pointer[1] << 8) + *s->pointer;
  Stream_Seek(s, 2uLL);

  // Check if the existing rectangle array is large enough
  if (bitmapUpdate->number > bitmapUpdate->count)
  {
    // Double the capacity (or set to 2 * number if count was 0)
    count = 2 * bitmapUpdate->number;
    
    // Reallocate the array of rectangles (sizeof(BITMAP_DATA) = 72 bytes)
    newdata = (BITMAP_DATA *)realloc(bitmapUpdate->rectangles, 72LL * count);
    if (!newdata)
      goto fail;
      
    bitmapUpdate->rectangles = newdata;
    
    // Zero out the newly allocated memory
    memset(&bitmapUpdate->rectangles[bitmapUpdate->count], 0, 72LL * (count - bitmapUpdate->count));
    bitmapUpdate->count = count;
  }

  // Read bitmap data for each rectangle
  for (i = 0; i < bitmapUpdate->number; ++i)
  {
    if (!update_read_bitmap_data(update, s, &bitmapUpdate->rectangles[i]))
      goto fail;
  }

  return bitmapUpdate;

fail:
  free_bitmap_update(update->context, bitmapUpdate);
  return NULL;
}