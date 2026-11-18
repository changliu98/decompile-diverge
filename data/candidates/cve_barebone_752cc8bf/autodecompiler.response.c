static void
prepare_singleton_class(mrb_state *mrb, struct RBasic *obj)
{
  struct RClass *cls;

  if (((((obj)->tt & 0xff)) == 12)) return;
  cls = (struct RClass*)mrb_obj_alloc(mrb, 12, mrb->object_class);
  cls->tt = ((1<<11) | ((((((cls->tt) >> 11) & 0x1fffff) | ((1<<11) | (((cls->tt) >> 11) & 0x1fffff))) << 11) | ((cls->tt) & 0x7ff)));
  cls->mt = mt_new(mrb);
  cls->flags = 0;
  if (((((obj)->tt & 0xff)) == 9)) {
    struct RClass *klass = ((struct RObject*)obj)->klass;
    if (!klass) {
      cls->super = mrb->object_class;
    }
    else {
      cls->super = klass->super;
    }
  }
  else if (((((obj)->tt & 0xff)) == 12)) {
    struct RClass *klass = ((struct RClass*)obj)->super;
    while (((((klass)->tt & 0xff)) == 11)) klass = ((struct RClass*)klass)->super;
    make_metaclass(mrb, klass->super);
    cls->super = klass->super;
  }
  else {
    cls->super = ((obj)->tt & 0xff) == 12 ? ((struct RClass*)obj)->super : ((obj)->tt & 0xff);
    prepare_singleton_class(mrb, (struct RBasic*)cls);
  }
  obj->klass = cls;
  mrb_field_write_barrier(mrb, (struct RBasic*)obj, (struct RBasic*)cls);
  mrb_field_write_barrier(mrb, (struct RBasic*)cls, (struct RBasic*)obj);
  mrb_obj_iv_set(mrb, (struct RBasic*)cls, 0, mrb_obj_value(obj));
  ((cls)->tt = (((((((cls)->tt) >> 11) & 0x1fffff) | ((((obj)->tt) >> 11) & 0x100000)) << 11) | ((cls)->tt) & 0x7ff));
}