void __cdecl reedSolomonComputeDivisor(int degree, uint8_t *result)
{
  int j; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]
  uint8_t root; // [rsp+Fh] [rbp-11h]

  if ( degree < 1 || degree > 30 )
    _assert_fail(
      "1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX",
      "func.c",
      0x16Au,
      "void reedSolomonComputeDivisor(int, uint8_t *)");
  memset(result, 0, degree);
  result[degree - 1] = 1;
  root = 1;
  for ( i = 0; i < degree; ++i )
  {
    for ( j = 0; j < degree; ++j )
    {
      result[j] = reedSolomonMultiply(result[j], root);
      if ( j + 1 < degree )
        result[j] ^= result[j + 1];
    }
    root = reedSolomonMultiply(root, 2u);
  }
}