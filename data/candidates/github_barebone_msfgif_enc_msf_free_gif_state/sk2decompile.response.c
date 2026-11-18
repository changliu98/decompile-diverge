void msf_free_gif_state(GIFState *gif) {
  GIFImage *img, *next;
  if (gif->gif_header.gif_data) free(gif->gif_header.gif_data);
  if (gif->gif_trailer.gif_data) free(gif->gif_trailer.gif_data);
  if (gif->gif_image_data) free(gif->gif_image_data);
  if (gif->gif_image_data_orig) free(gif->gif_image_data_orig);
  if (gif->gif_image_data_out) free(gif->gif_image_data_out);
  for (img = gif->gif_images; img; img = next) {
    next = img->next;
    free(img);
  }
  gif->gif_images = NULL;
}