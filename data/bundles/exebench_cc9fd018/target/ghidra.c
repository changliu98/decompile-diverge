int _safe_calloc_check_add(size_t a,size_t b,size_t *res)

{
  size_t *local_40;
  size_t tmp;
  size_t *res_local;
  size_t b_local;
  size_t a_local;
  
  local_40 = res;
  if (res == (size_t *)0x0) {
    local_40 = &tmp;
  }
  *local_40 = a + b;
  return (int)((CARRY8(a,b) ^ 0xffU) & 1);
}