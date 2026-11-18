char *emit_literal(char *p, const char *str, int len, _Bool fast)
{
 int l = len - 1;
 if (l < 61) {
  *p++ = (l << 2) | (fast & 1);
  if ((fast & 1) && len <= 16) {
   unaligned_copy64(str, p);
   unaligned_copy64(str + 8, p + 8);
   char *ret = p + len;
   return ret;
  }
 } else {
  char *orig_p = p;
  int count = 0;
  p++;
  for (;;) {
   if (!(l > 0))
    break;
   *p++ = l & 255;
   l >>= 8;
   count++;
  }
  (!(!(count >= 1))) ? (void)0 : ___assert_fail("!(!(count >= 1))", "./func.c", 583, "char *emit_literal(char *, const char *, int, _Bool)");
  (!(!(count <= 4))) ? (void)0 : ___assert_fail("!(!(count <= 4))", "./func.c", 584, "char *emit_literal(char *, const char *, int, _Bool)");
  *orig_p = (count + 59) << 2;
 }
 memcpy(p, str, len);
 char *ret = p + len;
 return ret;
}