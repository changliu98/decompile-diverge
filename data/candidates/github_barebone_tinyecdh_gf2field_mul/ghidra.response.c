void gf2field_mul(uint32_t *z,uint32_t *x,uint32_t *y)

{
  int iVar1;
  gf2elem_t tmp;
  int i;
  uint32_t *y_local;
  uint32_t *x_local;
  uint32_t *z_local;
  
  if (z != y) {
    bitvec_copy(tmp,x);
    iVar1 = bitvec_get_bit(y,0);
    if (iVar1 == 0) {
      bitvec_set_zero(z);
    }
    else {
      bitvec_copy(z,x);
    }
    for (i = 1; i < 0xa3; i = i + 1) {
      bitvec_lshift(tmp,tmp,1);
      iVar1 = bitvec_get_bit(tmp,0xa3);
      if (iVar1 != 0) {
        gf2field_add(tmp,tmp,polynomial);
      }
      iVar1 = bitvec_get_bit(y,i);
      if (iVar1 != 0) {
        gf2field_add(z,z,tmp);
      }
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("z != y","func.c",0x1c2,
                "void gf2field_mul(uint32_t *, const uint32_t *, const uint32_t *)");
}