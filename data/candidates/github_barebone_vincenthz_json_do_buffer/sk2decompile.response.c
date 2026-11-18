static int do_buffer(png_struct *png_ptr) {
  int ret = 0;
  if (png_ptr->process_mode >= 5 && png_ptr->process_mode <= 11) {
    ret = do_callback_withbuf(png_ptr, png_ptr->process_mode);
    if (ret) return ret;
  }
  png_ptr->buffer_size = 0;
  return ret;
}