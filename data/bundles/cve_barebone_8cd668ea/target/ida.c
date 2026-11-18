void __cdecl png_check_chunk_length(png_const_structrp png_ptr, const png_uint_32 length)
{
  int v2; // ecx
  png_uint_32 v3; // eax
  int v4; // ecx
  unsigned __int64 v5; // [rsp+8h] [rbp-48h]
  unsigned __int64 v6; // [rsp+10h] [rbp-40h]
  unsigned __int64 v7; // [rsp+18h] [rbp-38h]
  size_t row_factor; // [rsp+28h] [rbp-28h]
  png_alloc_size_t idat_limit; // [rsp+30h] [rbp-20h]
  png_alloc_size_t idat_limita; // [rsp+30h] [rbp-20h]
  unsigned __int64 limit; // [rsp+38h] [rbp-18h]

  limit = 0x7FFFFFFFLL;
  if ( png_ptr->user_chunk_malloc_max && png_ptr->user_chunk_malloc_max < 0x7FFFFFFF )
    limit = png_ptr->user_chunk_malloc_max;
  if ( png_ptr->chunk_name == 1229209940 )
  {
    v2 = 1;
    if ( png_ptr->bit_depth > 8u )
      v2 = 2;
    v3 = v2 * png_ptr->channels * png_ptr->width + 1;
    v4 = 0;
    if ( png_ptr->interlaced )
      v4 = 6;
    row_factor = v4 + v3;
    if ( png_ptr->height <= 0xFFFFFFFF / row_factor )
      idat_limit = row_factor * png_ptr->height;
    else
      idat_limit = 0x7FFFFFFFLL;
    if ( row_factor <= 0x7F36 )
      v7 = v4 + v3;
    else
      v7 = 32566LL;
    idat_limita = idat_limit + 5 * (idat_limit / v7 + 1) + 6;
    if ( idat_limita >= 0x7FFFFFFF )
      v6 = 0x7FFFFFFFLL;
    else
      v6 = idat_limita;
    if ( limit >= v6 )
      v5 = limit;
    else
      v5 = v6;
    limit = v5;
  }
  if ( length > limit )
    png_chunk_error(png_ptr, "chunk data is too large");
}