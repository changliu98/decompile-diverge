inline static int _safe_calloc_check_mul(size_t a, size_t b, size_t *res)
{
 size_t tmp;

 return !__builtin_mul_overflow(a, b, res ? res : &tmp);
}