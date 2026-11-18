void mrb_get_class(struct mrb_state *mrb, struct RBasic *obj)
{
  struct RBasic *class;
  struct RBasic *sc;
  if (((obj->flags & (0x10 | 0x1000)) == (0x10 | 0x1000)))
    return;
  class = (struct RBasic *)obj->c.data;
  sc = mrb_class_new(mrb, mrb_vtype_to_tt(mrb, obj->type), mrb->class_class);
  sc->type = mrb_vtype_to_tt(mrb, sc->type);
  sc->gcnext = mrb_gc_next(mrb);
  sc->c.data = ((void *)0);
  if (((obj->type & (0x1 | 0x10)) == (0x1 | 0x10))) {
    if (class->c.data == ((void *)0))
      class = mrb->class_class;
    else
      class = (struct RClass *)class->c.data;
    sc->c.data = (void *)class;
  }
  else if (((obj->type & (0x1 | 0x10)) == (0x1 | 0x1000))) {
    struct RBasic *class = obj;
    while ((class->type & (0x1 | 0x10)) == (0x1 | 0x10))
      class = (struct RBasic *)class->c.data;
    mrb_class_check(mrb, (struct RClass *)class->c.data);
    sc->c.data = (void *)class->c.data;
  }
  else {
    sc->c.data = (void *)class;
    mrb_get_class(mrb, sc);
  }
  obj->c.data = (void *)sc;
  mrb_set_iv((struct RObject *)obj, "$class", (struct RObject *)sc);
  mrb_set_iv((struct RObject *)sc, "$ivars", (struct RObject *)obj);
  class = mrb_get_iv(obj);
  mrb_set_iv((struct RObject *)sc, "$ivars", class);
  sc->type = obj->type;
}