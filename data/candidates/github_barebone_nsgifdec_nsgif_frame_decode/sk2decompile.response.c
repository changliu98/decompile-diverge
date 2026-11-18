nsgif_result nsgif_frame_decode(nsgif_gif *gif, int frame_index,
                                nsgif_image **image) {
  if (frame_index >= gif->header.num_frames) return 3;
  if (gif->current_frame == frame_index) {
    *image = gif->current_image;
    return 0;
  }
  int start_frame;
  if (gif->current_frame < frame_index && gif->current_frame != -1)
    start_frame = nsgif__frame_next(gif, 0, gif->current_frame);
  else
    start_frame = 0;
  for (int i = start_frame; i <= frame_index; i++) {
    nsgif_result result = nsgif__process_frame(gif, i, 1);
    if (result) return result;
  }
  *image = gif->current_image;
  return 0;
}