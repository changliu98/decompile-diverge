static BOOL clear_decompress_subcodecs_data(
    gdi_dc* dc, wStream* s, size_t subcodecs_length, size_t width, size_t height,
    void* buffer, int bpp, size_t pitch, size_t x_offset, size_t y_offset,
    size_t x_origin, size_t y_origin, size_t alpha_origin,
    wLog* log_functions) {
  size_t total_length = 0;
  if (!Stream_CheckAndLogRequiredLength("codec.clear", s, subcodecs_length)) {
    return 0;
  }
  while (total_length < subcodecs_length) {
    unsigned short x, y, w, h;
    unsigned int length;
    unsigned char subcode;
    if (!Stream_CheckAndLogRequiredLength("codec.clear", s, 13)) {
      return 0;
    }
    x = Stream_Get_UINT16(s);
    y = Stream_Get_UINT16(s);
    w = Stream_Get_UINT16(s);
    h = Stream_Get_UINT16(s);
    length = Stream_Get_UINT32(s);
    subcode = Stream_Get_UINT8(s);
    total_length += 13;
    if (!Stream_CheckAndLogRequiredLength("codec.clear", s, length)) {
      return 0;
    }
    {
      size_t x_end = x + x_offset;
      size_t y_end = y + y_offset;
      if (x_end + w > width) {
        return 0;
      }
      if (y_end + h > height) {
        return 0;
      }
      if (x_end + w > width) {
        return 0;
      }
      if (y_end + h > height) {
        return 0;
      }
    }
    if (!clear_resize_buffer(dc, w, h)) {
      return 0;
    }
    switch (subcode) {
      case 0: {
        size_t bytes = FreeRDPGetBytesPerPixel(0x19010128) * w;
        if (length != bytes * h) {
          return 0;
        }
        {
          void* data = Stream_Pointer(s);
          if (!convert_color(buffer, pitch, bpp, x + x_offset, y + y_offset, w,
                             h, data, bytes, 0x19010128, x_origin, y_origin,
                             log_functions)) {
            return 0;
          }
        }
        Stream_Seek(s, length);
        break;
      }
      case 1: {
        if (!clear_decompress_nscodec(dc->gdi, w, h, s, length, buffer, bpp,
                                      pitch, x + x_offset, y + y_offset)) {
          return 0;
        }
        break;
      }
      case 2: {
        if (!clear_decompress_subcode_rlex(s, length, w, h, buffer, bpp, pitch,
                                           x + x_offset, y + y_offset, x_origin,
                                           y_origin)) {
          return 0;
        }
        break;
      }
      default:
        return 0;
    }
    total_length += length;
  }
  return 1;
}