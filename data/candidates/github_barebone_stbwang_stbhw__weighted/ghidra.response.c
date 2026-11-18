int stbhw__weighted(int num_options,int *weights)

{
  int iVar1;
  int choice;
  int total;
  int k;
  int *weights_local;
  int num_options_local;
  
  total = 0;
  for (k = 0; k < num_options; k = k + 1) {
    total = weights[k] + total;
  }
  iVar1 = rand();
  iVar1 = (iVar1 >> 4) % total;
  total = 0;
  k = 0;
  while ((k < num_options && (total = weights[k] + total, total <= iVar1))) {
    k = k + 1;
  }
  if (num_options <= k) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("k < num_options","func.c",0x294,"int stbhw__weighted(int, int *)");
  }
  return k;
}