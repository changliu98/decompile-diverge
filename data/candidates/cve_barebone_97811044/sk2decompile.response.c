void iwjpeg_scan_exif_ifd(struct iw_jpeg_meta *meta, struct iw_jpeg_error *err,
                          unsigned int offset) {
  unsigned int n, i, tag_offset, tag;
  double dbl;
  if (offset < 8 || offset > err->data_size - 18) return;
  n = iw_get_ui16_e(err->data + offset, err->swap);
  if (n > 1000) return;
  for (i = 0; i < n; i++) {
    tag_offset = offset + 2 + i * 12;
    if (tag_offset + 12 > err->data_size) break;
    tag = iw_get_ui16_e(err->data + tag_offset, err->swap);
    switch (tag) {
      case 274:
        if (get_exif_tag_int_value(err, tag_offset, &tag))
          meta->orientation = tag;
        break;
      case 282:
        if (get_exif_tag_dbl_value(err, tag_offset, &dbl))
          meta->x_resolution = dbl;
        break;
      case 283:
        if (get_exif_tag_dbl_value(err, tag_offset, &dbl))
          meta->y_resolution = dbl;
        break;
      case 296:
        if (get_exif_tag_int_value(err, tag_offset, &tag))
          meta->resolution_unit = tag;
        break;
    }
  }
}