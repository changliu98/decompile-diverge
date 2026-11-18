int _safe_calloc_check_mul(size_t a,size_t b,size_t *res)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  size_t *local_40;
  size_t tmp;
  size_t *res_local;
  size_t b_local;
  size_t a_local;
  
  local_40 = res;
  if (res == (size_t *)0x0) {
    local_40 = &tmp;
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = a;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = b;
  *local_40 = SUB168(auVar1 * auVar2,0);
  return (int)((SUB168(auVar1 * auVar2,8) != 0 ^ 0xffU) & 1);
}