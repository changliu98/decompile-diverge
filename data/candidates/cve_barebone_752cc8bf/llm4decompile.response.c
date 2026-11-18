void
prepare_singleton_class(mrb_state *mrb, struct RObject *obj)
{
  struct RClass *c;

  if (((((struct RBasic*)(obj))->c)->tt) & 0xff) == 12) {
    return;
  }

  c = ((struct RClass *)(mrb_obj_alloc(mrb, MRB_TT_SCLASS, mrb->class_class)));
  (c)->flags |= 0x00020000;
  c->mt = mt_new(mrb);
  c->iv = NULL;

  if (((((struct RBasic*)(obj))->tt) & 0xff) == 9) {
    if (obj->metaclass) {
      c->super = ((struct RClass *)(obj->metaclass->c)->super);
    }
    else {
      c->super = mrb->class_class;
    }
  }
  else if (((((struct RBasic*)(obj))->tt) & 0xff) == 12) {
    struct RClass *meta = (struct RClass*)obj;
    while (((((struct RBasic*)(meta->super))->tt) & 0xff) == 11) {
      meta = meta->super;
    }
    make_metaclass(mrb, meta->super);
    c->super = meta->super->c;
  }
  else {
    c->super = obj->c;
    prepare_singleton_class(mrb, (struct RObject*)c);
  }
  obj->c = c;
  mrb_field_write_barrier(mrb, obj, (struct RBasic*)c);
  mrb_field_write_barrier(mrb, (struct RBasic*)c, (struct RBasic*)obj);
  mrb_obj_iv_set(mrb, (struct RObject*)c, 0, mrb_obj_value(obj));
  c->flags |= obj->flags & 0x00100000;
}