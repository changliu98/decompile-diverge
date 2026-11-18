static void process_bitmap_updates(ui_update_t *update) {
  int i, j;
  unsigned short num_bitmaps, x, y, x2, y2, width, height, bpp, bytes_per_pixel,
      compression, compressed_size;
  unsigned char *bitmap, *compressed_bitmap;
  logger(LOG_TRACE, LOG_COMPONENT_NAME, "%s()", "process_bitmap_updates");
  num_bitmaps = *((unsigned short *)update->data);
  update->data += 2;
  for (i = 0; i < num_bitmaps; i++) {
    x = *((unsigned short *)update->data);
    update->data += 2;
    y = *((unsigned short *)update->data);
    update->data += 2;
    x2 = *((unsigned short *)update->data);
    update->data += 2;
    y2 = *((unsigned short *)update->data);
    update->data += 2;
    width = *((unsigned short *)update->data);
    update->data += 2;
    height = *((unsigned short *)update->data);
    update->data += 2;
    bpp = *((unsigned short *)update->data);
    update->data += 2;
    bytes_per_pixel = (bpp + 7) / 8;
    compression = *((unsigned short *)update->data);
    update->data += 2;
    compressed_size = *((unsigned short *)update->data);
    update->data += 2;
    height = x2 - x + 1;
    bpp = y2 - y + 1;
    logger(LOG_DEBUG, LOG_COMPONENT_NAME,
           "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, "
           "compression=%d",
           x, y, x2, y2, width, height, bytes_per_pixel, compression);
    if (compression == 0) {
      bitmap = xmalloc(width * height * bytes_per_pixel);
      for (j = 0; j < height; j++) {
        memcpy(bitmap + (width * height - (j + 1) * width) * bytes_per_pixel,
               update->data, width * bytes_per_pixel);
        update->data += width * bytes_per_pixel;
      }
      ui_paint_bitmap(x, y, height, bpp, width, height, bitmap);
      xfree(bitmap);
    } else {
      unsigned short compressed_bitmap_size;
      if (compression & 0x400) {
        compressed_bitmap_size = compressed_size;
      } else {
        update->data += 2;
        compressed_bitmap_size = *((unsigned short *)update->data);
        update->data += 2;
        update->data += 4;
      }
      compressed_bitmap = update->data;
      update->data += compressed_bitmap_size;
      bitmap = xmalloc(width * height * bytes_per_pixel);
      if (bitmap_decompress(bitmap, width, height, compressed_bitmap,
                            compressed_bitmap_size, bytes_per_pixel)) {
        ui_paint_bitmap(x, y, height, bpp, width, height, bitmap);
      } else {
        logger(LOG_DEBUG, LOG_COMPONENT_UI,
               "process_bitmap_updates(), failed to decompress bitmap");
      }
      xfree(bitmap);
    }
  }
}