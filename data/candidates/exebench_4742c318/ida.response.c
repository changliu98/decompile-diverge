float __cdecl mayorDif(float *arrayLineal)
{
  float v2; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  float mayorTemp; // [rsp+8h] [rbp-10h]
  float mayor; // [rsp+Ch] [rbp-Ch]

  mayor = 0.0;
  for ( i = 0; arrayLineal[i + 1] != 0.0; ++i )
  {
    mayorTemp = arrayLineal[i] - arrayLineal[i + 1];
    if ( mayorTemp < 0.0 )
      LODWORD(v2) = _mm_cvtsi128_si32((__m128i)LODWORD(mayorTemp)) ^ 0x80000000;
    else
      v2 = arrayLineal[i] - arrayLineal[i + 1];
    if ( v2 > mayor )
      mayor = v2;
  }
  return mayor;
}