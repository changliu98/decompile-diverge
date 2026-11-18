void *mrb_realloc(mrb_state *mrb, void *ptr, size_t size) {
  void *p;
  p = mrb_realloc_simple(mrb, ptr, size);
  if (size == 0) return p;
  if (p) {
    mrb->flags &= ~(1 << 4);
  } else {
    mrb_free(mrb, ptr);
    mrb->flags |= (1 << 4);
    mrb->flags &= ~(1 << 3);
    mrb_raise_nomemory(mrb);
  }
  return p;
}