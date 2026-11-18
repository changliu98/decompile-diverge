static size_t func0(struct _Locale_collate* lcol,
                               wchar_t* dst, size_t dst_n, size_t dst_max,
                               const wchar_t* src, int c)
{ size_t n;
  size_t n1 = 1 << (src[2] & 0x00FF);
  size_t n2 = (size_t)src[3] * (1 << ((src[2] >> 8) & 0x00FF));
  if (n1!= dst_max) assert(!"unexpected dst_max");
  if (n2 > (dst_n * lcol->lc.multiplier)) { n = -1; goto lcol_error; }
  memcpy(dst + n2, lcol->lc.dummy, dst_max);
  n = dst_max;

 lcol_error:
  return n;
}