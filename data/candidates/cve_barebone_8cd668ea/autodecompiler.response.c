static void
png_check_chunk_length(png_structp png_ptr, png_uint_32 size)
{
   png_uint_32 limit = 0x7fffffffL;
   if (png_ptr->user_limit > 0 && png_ptr->user_limit < limit)
      limit = png_ptr->user_limit;

   if (png_ptr->chunk_type == (png_uint_32)0x49444154L)
   {
      unsigned long row_factor = (unsigned long)png_ptr->width *
         (unsigned long)png_ptr->bit_depth *
         (unsigned long)((png_ptr->channels * (png_ptr->pixel_size > 8 ? 2 : 1)) +
            (png_ptr->interlace_type != 0 ? 6 : 0)) + 1;
      unsigned long idat_limit = 0x7fffffffL;
      unsigned long irows = png_ptr->height;
      unsigned long ipos = 0xffffffffL / row_factor;
      unsigned long idat_size;
      unsigned long idat_rows;
      unsigned long idat_rows_max = 0x7f36L;

      if (irows > ipos)
         idat_limit = 0x7fffffffL;
      else
         idat_limit = (unsigned long)png_ptr->height * row_factor;

      if (row_factor > idat_rows_max)
         idat_rows = idat_rows_max;
      else
         idat_rows = row_factor;

      idat_size = idat_limit + ((idat_limit / idat_rows + 1) * 5 + 6);
      idat_limit = (idat_size < 0x7fffffffL ? idat_size : 0x7fffffffL);

      if (limit > idat_limit)
         limit = idat_limit;
   }

   if (size > limit)
      png_chunk_error(png_ptr, "chunk data is too large");
}