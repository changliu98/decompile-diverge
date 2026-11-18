static void initialise_banding(fz_context *ctx, band_writer *writer,
                               int band_list_preview) {
  int color_components, band_height, band_count, band_count_y;
  writer->band_format = band_format;
  writer->band_compression = band_compression;
  if (!band_list_preview) {
    if (writer->band_format == 1) {
      writer->band_format = 0;
      writer->band_compression = 0;
    } else if (writer->band_format == 2) {
      writer->band_format = 0;
      if (writer->band_compression == 4)
        writer->band_compression = 3;
      else
        writer->band_compression = 0;
    }
  }
  switch (writer->band_format) {
    case 0:
      color_components = 1;
      break;
    case 1:
      color_components = 2;
      break;
    default:
      color_components = 3;
      break;
  }
  band_height =
      INT_MAX / (writer->page_bbox.x1 - writer->page_bbox.x0) *
      (writer->page_bbox.y1 - writer->page_bbox.y0) * color_components;
  if (band_height < 1) band_height = 1;
  if (writer->band_count_y > 0) {
    band_count = (writer->page_bbox.y1 - writer->page_bbox.y0 +
                  band_count_y_overlap - 1) /
                 band_count_y_overlap;
    band_count_y = (band_count + band_height - 1) / band_height;
    band_count_y =
        (band_count_y * writer->band_count_y + writer->band_count_y - 1) /
        writer->band_count_y;
    band_height = (band_count + band_count_y - 1) / band_count_y;
  }
  writer->band_height = band_height;
  writer->band_number = 0;
  if (band_compression == 0 || band_compression == 1) {
    writer->band_writer = fz_new_pnm_band_writer(ctx, band_compression_level);
    writer->band_bits = band_compression ? 3 : 1;
  } else if (band_compression == 2) {
    writer->band_writer = fz_new_pam_band_writer(ctx, band_compression_level);
    writer->band_bits = 4;
  } else if (band_compression == 3) {
    writer->band_writer = fz_new_pbm_band_writer(ctx, band_compression_level);
    writer->band_bits = 1;
  } else if (band_compression == 4) {
    writer->band_writer = fz_new_pkm_band_writer(ctx, band_compression_level);
    writer->band_bits = 4;
  }
}