void __cdecl png_check_chunk_length(png_const_structrp png_ptr, const png_uint_32 length)
{
  png_alloc_size_t row_factor;
  png_alloc_size_t idat_limit;
  png_alloc_size_t limit = PNG_USER_CHUNK_MALLOC_MAX; // 0x7FFFFFFF

  if (png_ptr->user_chunk_malloc_max && png_ptr->user_chunk_malloc_max < PNG_USER_CHUNK_MALLOC_MAX)
    limit = png_ptr->user_chunk_malloc_max;

  // 1229209940 is 'IDAT' in little-endian ASCII
  if (png_ptr->chunk_name == 1229209940)
  {
    int pixel_factor = (png_ptr->bit_depth > 8u) ? 2 : 1;
    int interlace_factor = png_ptr->interlaced ? 6 : 0;
    
    // v3: size of a row's pixel data + filter byte
    png_alloc_size_t row_bytes = pixel_factor * png_ptr->channels * png_ptr->width + 1;
    
    row_factor = interlace_factor + row_bytes;

    // Check for overflow before multiplying by height
    if (png_ptr->height <= 0xFFFFFFFF / row_factor)
      idat_limit = row_factor * png_ptr->height;
    else
      idat_limit = PNG_USER_CHUNK_MALLOC_MAX;

    // Determine the compression overhead factor (v7)
    png_alloc_size_t comp_overhead;
    if (row_factor <= 0x7F36)
      comp_overhead = row_factor;
    else
      comp_overhead = 32566; // 0x7F36

    // Calculate the final IDAT limit with zlib overhead
    idat_limit = idat_limit + 5 * (idat_limit / comp_overhead + 1) + 6;

    // Clamp the calculated IDAT limit to the maximum allowed size
    if (idat_limit >= PNG_USER_CHUNK_MALLOC_MAX)
      idat_limit = PNG_USER_CHUNK_MALLOC_MAX;

    // Use the larger of the pre-existing limit and the calculated IDAT limit
    if (idat_limit > limit)
      limit = idat_limit;
  }

  if (length > limit)
    png_chunk_error(png_ptr, "chunk data is too large");
}