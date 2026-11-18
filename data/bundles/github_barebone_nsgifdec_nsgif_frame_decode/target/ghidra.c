nsgif_error nsgif_frame_decode(nsgif_t *gif,uint32_t frame,nsgif_bitmap_t **bitmap)

{
  nsgif_error nVar1;
  uint32_t f;
  nsgif_error ret;
  uint32_t start_frame;
  nsgif_bitmap_t **bitmap_local;
  uint32_t frame_local;
  nsgif_t *gif_local;
  nsgif_error local_c;
  
  if (frame < (gif->info).frame_count) {
    if (gif->decoded_frame == frame) {
      *bitmap = gif->frame_image;
      local_c = NSGIF_OK;
    }
    else {
      if ((gif->decoded_frame < frame) && (gif->decoded_frame != 0xffffffff)) {
        start_frame = nsgif__frame_next(gif,false,gif->decoded_frame);
      }
      else {
        start_frame = 0;
      }
      for (f = start_frame; f <= frame; f = f + 1) {
        nVar1 = nsgif__process_frame(gif,f,true);
        if (nVar1 != NSGIF_OK) {
          return nVar1;
        }
      }
      *bitmap = gif->frame_image;
      local_c = NSGIF_OK;
    }
  }
  else {
    local_c = NSGIF_ERR_BAD_FRAME;
  }
  return local_c;
}