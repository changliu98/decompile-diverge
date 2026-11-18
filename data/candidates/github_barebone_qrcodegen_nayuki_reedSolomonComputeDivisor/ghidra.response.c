void reedSolomonComputeDivisor(int degree,uint8_t *result)

{
  uint8_t uVar1;
  int j;
  int i;
  uint8_t root;
  uint8_t *result_local;
  int degree_local;
  
  if ((0 < degree) && (degree < 0x1f)) {
    memset(result,0,(long)degree);
    result[degree + -1] = '\x01';
    root = '\x01';
    for (i = 0; i < degree; i = i + 1) {
      for (j = 0; j < degree; j = j + 1) {
        uVar1 = reedSolomonMultiply(result[j],root);
        result[j] = uVar1;
        if (j + 1 < degree) {
          result[j] = result[j] ^ result[j + 1];
        }
      }
      root = reedSolomonMultiply(root,'\x02');
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("1 <= degree && degree <= qrcodegen_REED_SOLOMON_DEGREE_MAX","func.c",0x16a,
                "void reedSolomonComputeDivisor(int, uint8_t *)");
}