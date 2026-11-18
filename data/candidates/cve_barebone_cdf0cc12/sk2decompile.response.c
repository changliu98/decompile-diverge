static BitmapUpdate* update_read_bitmap_update(WMFReader* wmfreader,
                                               Stream* s) {
  BitmapUpdate* bitmap_update;
  int i;
  bitmap_update = (BitmapUpdate*)calloc(1, sizeof(BitmapUpdate));
  if (bitmap_update == NULL) goto fail;
  if (Stream_GetRemainingLength(s) < 2) goto fail;
  bitmap_update->num_rects = (((unsigned short)((unsigned char*)s->pos)[1]
                                << 8) +
                               (unsigned char*)s->pos)[0];
  Stream_Seek(s, 2);
  if (bitmap_update->num_rects > bitmap_update->allocated_rects) {
    int new_allocated_rects = bitmap_update->num_rects * 2;
    WMFRECT* new_rects;
    new_rects = (WMFRECT*)realloc(
        bitmap_update->rects, new_allocated_rects * sizeof(WMFRECT));
    if (new_rects == NULL) goto fail;
    bitmap_update->rects = new_rects;
    memset(bitmap_update->rects + bitmap_update->allocated_rects, 0,
           (new_allocated_rects - bitmap_update->allocated_rects) *
               sizeof(WMFRECT));
    bitmap_update->allocated_rects = new_allocated_rects;
  }
  for (i = 0; i < bitmap_update->num_rects; i++) {
    if (update_read_bitmap_data(wmfreader, s, &bitmap_update->rects[i]) == 0)
      goto fail;
  }
  return bitmap_update;
fail:
  free_bitmap_update(wmfreader->mem_stream, bitmap_update);
  return NULL;
}