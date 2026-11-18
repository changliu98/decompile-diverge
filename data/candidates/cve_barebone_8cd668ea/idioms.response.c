void png_check_chunk_length(struct png_structp png_ptr, unsigned long length)
{
   unsigned long max = (1 << (sizeof(png_size_t)*8 - 1)) - 1;
   if (png_ptr->user_chunk_malloc_max != (png_size_t) 0
      && png_ptr->user_chunk_malloc_max < (png_size_t) max)
      max = png_ptr->user_chunk_malloc_max;
   if (png_ptr->chunk_name == (unsigned int) 'zTXt')
   {
      unsigned long row_factor = 1 +
         ((png_ptr->bit_depth > 8) ? 2 : 1) *
         png_ptr->channels *
         png_ptr->width +
         ((png_ptr->interlaced) ? 6 : 0);
      unsigned long idat_limit =
         ((png_ptr->height > (png_size_t) (0x7fffffff / row_factor))
          ? (png_size_t) (0x7fffffff / row_factor) :
          row_factor * png_ptr->height);
      unsigned long idat_limita = idat_limit +
         ((idat_limit /
           ((row_factor > (png_size_t) (0x7fffffff / 32566))
            ? (png_size_t) (0x7fffffff / 32566) :
            row_factor)) * 5) +
         6;
      unsigned long idat_limitb =
         ((idat_limita > (png_size_t) (0x7fffffff / 1))
          ? (png_size_t) (0x7fffffff / 1) :
          idat_limita);
      unsigned long idat_limitc =
         ((max > (png_size_t) (0x7fffffff / 1))
          ? (png_size_t) (0x7fffffff / 1) :
          max);
      max =
         ((idat_limitc < idat_limitb) ? (idat_limitc) :
          (idat_limitb));
   }
   if (length > max)
      png_error(png_ptr, "chunk data is too large");
}