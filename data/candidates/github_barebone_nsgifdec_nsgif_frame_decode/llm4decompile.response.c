nsgif_error nsgif_frame_decode(nsgif_t *gif, uint32_t frame, nsgif_bitmap_t **bitmap)
{
 if (frame >= gif->info.frame_count) {
  return NSGIF_ERR_BAD_FRAME;
 }

 if (frame == gif->decoded_frame) {
  *bitmap = gif->frame_image;
  return NSGIF_OK;
 }

 uint32_t start_frame = 0;
 if (gif->decoded_frame < frame && gif->decoded_frame != (uint32_t)-1) {
  start_frame = nsgif__frame_next(gif, false, gif->decoded_frame);
 }

 for (uint32_t f = start_frame; f <= frame; f++) {
  nsgif_error err = nsgif__process_frame(gif, f, true);
  if (err != NSGIF_OK) {
   return err;
  }
 }

 *bitmap = gif->frame_image;

 return NSGIF_OK;
}