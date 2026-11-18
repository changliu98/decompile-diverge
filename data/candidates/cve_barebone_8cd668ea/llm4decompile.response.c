void
png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
   png_alloc_size_t user_limit;

   user_limit = ((png_ptr->user_chunk_malloc_max) == 0 ?
      ((png_alloc_size_t)(((png_uint_32)(2147483647L)) >> (0))) :
      (png_ptr->user_chunk_malloc_max));

   if (user_limit < ((png_alloc_size_t)(((png_uint_32)(2147483647L)) >> (0))))
      user_limit = user_limit;

   if (png_ptr->chunk_name == (((png_bytep)(png_charp)("IDAT"))[0] | ((png_bytep)(png_charp)("IDAT"))[1] | ((png_bytep)(png_charp)("IDAT"))[2] | ((png_bytep)(png_charp)("IDAT"))[3] << 8))
   {
      png_uint_32 max_idat_size;
      png_uint_32 max_block_size;
      png_uint_32 max_block_count;
      png_uint_32 max_block_header;
      png_uint_32 max_block_overhead;
      png_uint_32 max_block_length;
      png_uint_32 max_idat_length;

      max_block_length = 32768;
      max_block_header = 5;
      max_block_overhead = 12;

      max_block_size = (png_uint_32)png_ptr->width *
         (png_uint_32)png_ptr->channels *
         ((png_ptr->bit_depth) > 8 ? 2 : 1) + 1;

      if (png_ptr->interlaced)
         max_block_size += 6;

      if (png_ptr->height <= (png_uint_32)(((png_uint_32)(2147483647L)) >> (0)) / max_block_size)
         max_idat_size = max_block_size * png_ptr->height;
      else
         max_idat_size = ((png_uint_32)(2147483647L));

      if (max_block_length > max_block_size)
         max_block_size = max_block_length;

      max_block_count = max_idat_size / max_block_size + 1;

      max_idat_length = max_idat_size +
         max_block_header * max_block_count +
         max_block_overhead;

      if (max_idat_length > ((png_uint_32)(2147483647L)))
         max_idat_length = ((png_uint_32)(2147483647L));

      if (user_limit > max_idat_length)
         user_limit = max_idat_length;
   }

   if (length > user_limit)
      png_chunk_error(png_ptr, "chunk data is too large");
}