static RD_BOOL
process_bitmap_updates(RDPCLIENT * This, STREAM s)
{
 unsigned int i;
 BITMAP_UPDATE *bitmapUpdate = (BITMAP_UPDATE *) calloc(1, sizeof(BITMAP_UPDATE));
 if(bitmapUpdate == NULL)
 {
  return (0);
 }
 if(Stream_GetRemainingLength(s) < 3)
 {
  goto error;
 }
 while (1)
 {
  do { (bitmapUpdate->number_of_bitmaps) = ((unsigned short)((*((unsigned char*)((s)->p + (0)) + 0)) + ((*((unsigned char*)((s)->p + (0)) + 1)) << 8))); } while (0);
  Stream_Seek(s, 2);
  if(bitmapUpdate->number_of_bitmaps > bitmapUpdate->allocated_number_of_bitmaps)
  {
   unsigned short new_count;
   BITMAP_DATA *new_data;

   new_count = bitmapUpdate->number_of_bitmaps * 2;
   new_data = (BITMAP_DATA *) realloc(bitmapUpdate->bitmap_data, new_count * sizeof(BITMAP_DATA));
   if(new_data == NULL)
   {
    goto error;
   }
   bitmapUpdate->bitmap_data = new_data;
   memset(&bitmapUpdate->bitmap_data[bitmapUpdate->allocated_number_of_bitmaps], 0,
          (new_count - bitmapUpdate->allocated_number_of_bitmaps) * sizeof(BITMAP_DATA));
   bitmapUpdate->allocated_number_of_bitmaps = new_count;
  }

  for (i = 0; i < bitmapUpdate->number_of_bitmaps; i++)
  {
   if(!update_read_bitmap_data(This, s, &bitmapUpdate->bitmap_data[i]))
   {
    goto error;
   }
  }
  break;
 }
 return (1);

      error:
 free_bitmap_update(This->rdpcontext, bitmapUpdate);
 return (0);
}