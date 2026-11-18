void
png_64bit_product(png_uint_32 a, png_uint_32 b, png_uint_32 *hi_product,
   png_uint_32 *lo_product)
{
   png_uint_16 a_lo = (png_uint_16)(a & 0xffff);
   png_uint_16 a_hi = (png_uint_16)((a >> 16) & 0xffff);
   png_uint_16 b_lo = (png_uint_16)(b & 0xffff);
   png_uint_16 b_hi = (png_uint_16)((b >> 16) & 0xffff);

   png_uint_32 tmp1 = (png_uint_32)a_lo * b_lo;
   png_uint_32 tmp2 = (png_uint_32)a_hi * b_lo;
   png_uint_32 tmp3 = (png_uint_32)a_lo * b_hi;
   png_uint_32 tmp4 = (png_uint_32)a_hi * b_hi;

   png_uint_32 lo_product_tmp = (tmp1 & 0xffff) |
      (((tmp2 + tmp3) & 0xffff) << 16);

   *hi_product = (tmp4 + ((tmp2 + tmp3) >> 16)) & 0xffff;
   *lo_product = lo_product_tmp;
}