void * mrb_realloc(mrb_state *mrb,void *p,size_t len)

{
  void *pvVar1;
  void *p2;
  size_t len_local;
  void *p_local;
  mrb_state *mrb_local;
  
  pvVar1 = mrb_realloc_simple(mrb,p,len);
  if (len != 0) {
    if (pvVar1 == (void *)0x0) {
      mrb_free(mrb,p);
      (mrb->gc).out_of_memory = '\x01';
      mrb_raise_nomemory(mrb);
    }
    else {
      (mrb->gc).out_of_memory = '\0';
    }
  }
  return pvVar1;
}