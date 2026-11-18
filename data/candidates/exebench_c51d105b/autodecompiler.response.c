void png_64bit_product(int32_t a, int32_t b, uint32_t *hi, uint32_t *lo){
 uint32_t ahi, alo, bhi, blo;
 uint32_t c0, c1, c2;
 int32_t c1_a, c1_b;

 ahi = (a >> 16) & 0xffff;
 alo = a & 0xffff;
 bhi = (b >> 16) & 0xffff;
 blo = b & 0xffff;

 c0 = alo * blo;
 c1_a = ahi * blo;
 c1_b = bhi * alo;
 c1 = c1_a + c1_b;
 c2 = ahi * bhi;

 c2 += ((c1 >> 16) & 0xffff);
 c1 = ((c1 & 0xffff) << 16) | (c0 & 0xffff);
 c2 += ((c1 >> 16) & 0xffff);

 *hi = c2;
 *lo = c1;
}