void unpackFloat(float aV, int *exponent, int *magnitude) {
   int a = *((int *) ((void *) &aV));
   *exponent = ((((int) a) & 0x7F800000) >> 23) - 127;
   *magnitude = (a & 0x007FFFFF) + (0x007FFFFF + 1);
   if (a & 0x80000000)
    *magnitude = -*magnitude;



}