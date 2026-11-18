void*
mrb_realloc(mrb_state *mrb, void *ptr, size_t size)
{
  void *p;

  p = mrb_realloc_simple(mrb, ptr, size);
  if (size != 0) {
    if (p == NULL) {
      mrb_free(mrb, ptr);
      mrb->gc.out_of_memory = 1;
      mrb_raise_nomemory(mrb);
    }
    else {
      mrb->gc.out_of_memory = 0;
    }
  }
  return p;
}