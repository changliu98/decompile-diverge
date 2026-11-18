void __cdecl get_bits_exp(double x, double *a, int *n)
{
  double t2; // [rsp+10h] [rbp-28h]
  double t2a; // [rsp+10h] [rbp-28h]

  HIDWORD(t2) = HIDWORD(x) & 0x7FF00000;
  if ( HIDWORD(x) )
  {
    LODWORD(t2) = 0;
    *n = (HIDWORD(t2) >> 20) - 1023;
  }
  else
  {
    *(_QWORD *)&t2a = COERCE_UNSIGNED_INT64(
                        1024.0
                      * COERCE_DOUBLE((unsigned __int64)LODWORD(x))
                      * 1024.0
                      * 1024.0
                      * 1024.0
                      * 1024.0
                      * 1024.0) & 0x7FF0000000000000LL;
    *n = (HIDWORD(t2a) >> 20) - 1083;
    t2 = t2a / 1.152921504606847e18;
  }
  *a = x / t2;
}