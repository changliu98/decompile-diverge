void *mrb_realloc(struct mrb_state *mrb, void *ptr, unsigned long len)
{
  void *ret = mrb_realloc_func(mrb, ptr, len);
  if (len == 0) {
    return ret;
  }
  if (ret == ((void *)0)) {
    mrb_free(mrb, ptr);
    mrb->gc.check_interval = mrb->gc.check_interval & ~0x10 | 0x10;
    mrb_gc_check(mrb);
  }
  else {
    mrb->gc.check_interval = mrb->gc.check_interval & ~0x10;
  }
  return ret;
}