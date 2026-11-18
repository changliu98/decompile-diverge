void __cdecl png_64bit_product(long v1, long v2, unsigned __int64 *hi_product, unsigned __int64 *lo_product)
{
  *hi_product = (((unsigned __int16)v1 * WORD1(v2)
                + (unsigned __int16)v2 * WORD1(v1)
                + (((unsigned __int16)v2 * (unsigned int)(unsigned __int16)v1) >> 16)) >> 16)
              + (__int64)(WORD1(v2) * WORD1(v1));
  *lo_product = (unsigned int)(v1 * v2);
}