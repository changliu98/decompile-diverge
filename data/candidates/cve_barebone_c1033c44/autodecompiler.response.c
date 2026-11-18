void *
mrb_realloc(mrb_state *mrb, void *p, size_t len)
{
  void *ret;
  ret = mrb_realloc_simple(mrb, p, len);
  if (len > 0) {
    if (ret == NULL) {
      mrb_free(mrb, p);
      ((mrb)->flags = (((mrb)->flags & ~0x10) | (!0 << 4)));
      mrb_raise_nomemory(mrb);
    }
    else {
      ((mrb)->flags = (((mrb)->flags & ~0x10) | (0 << 4)));
    }
  }
  return ret;
}