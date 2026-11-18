static int func0(const uint8_t* const src, size_t src_size,
                         uint8_t* const dst, size_t dst_size,
                         const WebPPicture* const pic,
                         const VP8LBitWriter* const bw) {
  int ok = 1;
  if (src_size & 0xF) {
    ok = 0;
  } else {
    const int num_pixels = (int)src_size >> 4;
    uint32_t prev_y = bw->prev_y_;
    uint32_t prev_u = bw->prev_u_;
    int i;
    for (i = 0; i < num_pixels; ++i) {
      const uint32_t y = *src++;
      const uint32_t u = *src++;
      uint32_t x, yy;
      VP8LBitWriterGet(y, &x, dst, dst_size, pic);
      VP8LBitWriterGet(u, &yy, &prev_y, prev_u, 16);
      dst[0] = x;
      dst[1] = yy;
      prev_u = u;
    }
  }
  return ok;
}