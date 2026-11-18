void stack4_replace_top(stack4 *s, uintptr_t e) {
  uintptr_t t = s->top;
  t = (t & ~(uintptr_t)0xf) | e;
  s->top = t;
}