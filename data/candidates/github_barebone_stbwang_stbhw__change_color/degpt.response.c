int stbhw__change_color(int old_color,int num_options,int *weights)

{
  int iVar1;
  int offset;
  int choice;
  int total;
  int k;
  int *weights_local;
  int num_options_local;
  int old_color_local;
  int local_c;
  
  if (weights == (int *)0x0) {
    iVar1 = rand();
    local_c = (old_color + (iVar1 >> 4) % (num_options + -1) + 1) % num_options;
  }
  else {
    total = 0;
    for (k = 0; k < num_options; k = k + 1) {
      if (k != old_color) {
        total = weights[k] + total;
      }
    }
    iVar1 = rand();
    iVar1 = (iVar1 >> 4) % total;
    total = 0;
    k = 0;
    while ((k < num_options && ((k == old_color || (total = weights[k] + total, total <= iVar1)))))
    {
      k = k + 1;
    }
    if (num_options <= k) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("k < num_options","func.c",0x2a9,"int stbhw__change_color(int, int, int *)");
    }
    local_c = k;
  }
  return local_c;
}