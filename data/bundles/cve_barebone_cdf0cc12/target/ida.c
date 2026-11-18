BITMAP_UPDATE *__cdecl update_read_bitmap_update(rdpUpdate *update, wStream *s)
{
  BITMAP_DATA *newdata; // [rsp+8h] [rbp-38h]
  UINT16 count; // [rsp+16h] [rbp-2Ah]
  BITMAP_UPDATE *bitmapUpdate; // [rsp+18h] [rbp-28h]
  UINT32 i; // [rsp+24h] [rbp-1Ch]

  bitmapUpdate = (BITMAP_UPDATE *)calloc(1uLL, 0x18uLL);
  if ( !bitmapUpdate || Stream_GetRemainingLength(s) < 2 )
    goto fail;
  bitmapUpdate->number = (unsigned __int16)(s->pointer[1] << 8) + *s->pointer;
  Stream_Seek(s, 2uLL);
  if ( bitmapUpdate->number <= bitmapUpdate->count )
    goto LABEL_6;
  count = 2 * bitmapUpdate->number;
  newdata = (BITMAP_DATA *)realloc(bitmapUpdate->rectangles, 72LL * count);
  if ( !newdata )
  {
fail:
    free_bitmap_update(update->context, bitmapUpdate);
    return 0LL;
  }
  bitmapUpdate->rectangles = newdata;
  memset(&bitmapUpdate->rectangles[bitmapUpdate->count], 0, 72LL * (count - bitmapUpdate->count));
  bitmapUpdate->count = count;
LABEL_6:
  for ( i = 0; i < bitmapUpdate->number; ++i )
  {
    if ( !update_read_bitmap_data(update, s, &bitmapUpdate->rectangles[i]) )
      goto fail;
  }
  return bitmapUpdate;
}