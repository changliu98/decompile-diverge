void gf2field_mul(uint32_t *z, const uint32_t *y, const uint32_t *x) {
  int i;
  bitvec_t tmp;
  {
# 450 "func.c"
    if (!(z != x)) {
# 450 "func.c"
      __assert_fail("z != y");
    }
# 451 "func.c"
    bitvec_copy(tmp, y);
# 452 "func.c"
    if (bitvec_get_bit(x, 0)) {
# 453 "func.c"
      bitvec_copy(z, y);
    } else {
# 455 "func.c"
      bitvec_set_zero(z);
    }
# 457 "func.c"
    i = 1;
    {
# 457 "func.c"
      while (1) {
      while_continue:;
# 457 "func.c"
        if (i < 163) {
        } else {
# 457 "func.c"
          goto while_break;
        }
# 458 "func.c"
        bitvec_lshift(tmp, tmp, 1);
# 459 "func.c"
        if (bitvec_get_bit(tmp, 163)) {
# 460 "func.c"
          gf2field_add(tmp, tmp, (uint32_t *)((void *)&gf2field_reduction_poly));
        }
# 462 "func.c"
        if (bitvec_get_bit(x, i)) {
# 463 "func.c"
          gf2field_add(z, z, tmp);
        }
# 457 "func.c"
        i = i + 1;
      }
    while_break:;
    }
# 466 "func.c"
    return;
  }
}