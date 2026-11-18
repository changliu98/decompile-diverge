struct BITMAP_UPDATE *update_read_bitmap_update(struct rdp_update *update, struct wStream *s)
{
  struct BITMAP_UPDATE *bitmapUpdate;
  struct BITMAP_DATA *data;
  unsigned int i;
  unsigned short count;
  bitmapUpdate = (struct BITMAP_UPDATE *)calloc(1, sizeof(BITMAP_UPDATE));
  if (bitmapUpdate == ((void *)0))
    goto fail;
  if (Stream_GetRemainingLength(s) < 2)
    goto fail;
  bitmapUpdate->number = s->pointer[0] + (s->pointer[1] * 256);
  Stream_Seek(s, 2);
  if (bitmapUpdate->number > bitmapUpdate->count)
  {
    count = (unsigned short)(bitmapUpdate->number * 2);
    data = (struct BITMAP_DATA *)realloc(bitmapUpdate->rectangles,
      count * sizeof(BITMAP_DATA));
    if (data == ((void *)0))
      goto fail;
    bitmapUpdate->rectangles = data;
    memset(&bitmapUpdate->rectangles[bitmapUpdate->count], 0,
      (count - bitmapUpdate->count) * sizeof(BITMAP_DATA));
    bitmapUpdate->count = count;
  }
  for (i = 0; i < bitmapUpdate->number; i++)
  {
    if (update_read_bitmap_data(update, s, &bitmapUpdate->rectangles[i]) == ((void *)0))
      goto fail;
  }
  return bitmapUpdate;
fail:
  free_bitmap_update(update->context, bitmapUpdate);
  return ((void *)0);
}