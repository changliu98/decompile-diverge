int __cdecl safe_calloc_check_add(size_t a, size_t b, size_t *res)
{
  size_t *p_tmp; // [rsp+0h] [rbp-38h]
  size_t tmp; // [rsp+18h] [rbp-20h] BYREF
  size_t *resa; // [rsp+20h] [rbp-18h]
  size_t ba; // [rsp+28h] [rbp-10h]
  size_t aa; // [rsp+30h] [rbp-8h]

  aa = a;
  ba = b;
  resa = res;
  if ( res )
    p_tmp = resa;
  else
    p_tmp = &tmp;
  *p_tmp = b + a;
  return !__CFADD__(b, a);
}