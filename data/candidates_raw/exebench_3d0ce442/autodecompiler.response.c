float rand_float(int *seed)
{
 int flt_mant, flt_exp = 30, bit_31;
 float flt_rnd;

 *seed = 1234571 * (*seed) + 910801;
 bit_31 = (*seed & 0x7f000000);
 flt_mant = bit_31 >> 3;
 flt_rnd = (float)(0x1e000000 | flt_mant);

 return flt_rnd;
}