int __cdecl safe_calloc_check_add(size_t a, size_t b, size_t *res)
{
  size_t tmp;

  if (!res)
    res = &tmp;

  *res = a + b;
  return !__CFADD__(a, b);
}