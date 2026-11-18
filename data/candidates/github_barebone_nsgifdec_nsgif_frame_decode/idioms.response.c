enum nsgif_error nsgif_frame_decode(struct nsgif *gif, unsigned int frame, struct nsgif_bitmap **bitmap)
{
  if (frame >= gif->info.frame_count)
    return NSGIF_ERROR_FRAMENO;
  if (gif->decoded_frame == frame) {
    *bitmap = gif->frame_image;
    return NSGIF_OK;
  }
  if (gif->decoded_frame < frame && gif->decoded_frame != -1) {
    unsigned int start = nsgif__frame_next(gif, 0, gif->decoded_frame);
    unsigned int i;
    for (i = start; i <= frame; i++) {
      enum nsgif_error e = nsgif__process_frame(gif, i, 1);
      if (e != NSGIF_OK)
        return e;
    }
  }
  else
    for (unsigned int i = 0; i <= frame; i++) {
      enum nsgif_error e = nsgif__process_frame(gif, i, 1);
      if (e != NSGIF_OK)
        return e;
    }
  *bitmap = gif->frame_image;
  return NSGIF_OK;
}