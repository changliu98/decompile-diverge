void png_check_chunk_length(png_structp png_ptr, png_uint_32 length) {
  png_uint_32 max_length = 0x7fffffff;
  if (png_ptr->chunk_max_size != 0 && png_ptr->chunk_max_size < max_length)
    max_length = png_ptr->chunk_max_size;
  if (png_ptr->chunk_name == (0x49444154L)) {
    png_uint_32 image_data_size =
        png_ptr->width * (png_ptr->bit_depth > 8 ? 2 : 1);
    png_uint_32 ancillary_size = png_ptr->interlaced ? 6 : 0;
    png_uint_32 row_size = image_data_size + ancillary_size + 1;
    png_uint_32 num_rows;
    png_uint_32 chunk_length;
    if (png_ptr->height > 0xffffffffL / row_size)
      num_rows = 0x7fffffff;
    else
      num_rows = png_ptr->height * row_size;
    chunk_length =
        num_rows + 6 +
        (num_rows / (row_size > 32566 ? 32566 : row_size) + 1) * 5;
    if (chunk_length > 0x7fffffff) chunk_length = 0x7fffffff;
    if (chunk_length < max_length) max_length = chunk_length;
  }
  if (length > max_length) png_chunk_error(png_ptr, "chunk data is too large");
}