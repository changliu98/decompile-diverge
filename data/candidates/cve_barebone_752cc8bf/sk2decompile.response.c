static void prepare_singleton_class(mrb_state *mrb, struct RClass *c) {
  struct RClass *sc;
  if (((((c)->tt) & 0xff) == 12)) return;
  sc = mrb_obj_alloc(mrb, MRB_TT_ICLASS, mrb->class_class);
  do {
    mrb_object *obj = (mrb_object *)(sc);
    obj->flags |= (1 << 17);
  } while (0);
  sc->cpath = mt_new(mrb);
  sc->super = NULL;
  if (((((c)->tt) & 0xff) == 9)) {
    if (c->super) {
      sc->super = c->super->c;
    } else {
      sc->super = mrb->class_class;
    }
  } else if (((((c)->tt) & 0xff) == 12)) {
    struct RClass *s = c;
    while (((((s->super)->tt) & 0xff) == 11)) {
      s = s->super;
    }
    make_metaclass(mrb, s->super);
    sc->super = s->super->c;
  } else {
    sc->super = c->c;
    prepare_singleton_class(mrb, sc);
  }
  c->c = sc;
  mrb_field_write_barrier(mrb, c, sc);
  mrb_field_write_barrier(mrb, sc, c);
  mrb_obj_iv_set(mrb, sc, 0, mrb_obj_value(c));
  do {
    mrb_object *obj = (mrb_object *)(sc);
    obj->flags |= ((((mrb_object *)(c))->flags) & (1 << 20));
  } while (0);
}