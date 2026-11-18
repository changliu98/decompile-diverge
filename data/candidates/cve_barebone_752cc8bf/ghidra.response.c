void prepare_singleton_class(mrb_state *mrb,RBasic *o)

{
  RClass *obj;
  mt_tbl *pmVar1;
  mrb_value mVar2;
  mrb_value v;
  RClass *c;
  RClass *sc;
  RBasic *o_local;
  mrb_state *mrb_local;
  
  if ((*(uint *)&o->c->tt & 0xff) != 0xc) {
    obj = (RClass *)mrb_obj_alloc(mrb,MRB_TT_SCLASS,mrb->class_class);
    obj->flags = obj->flags | 0x20000;
    pmVar1 = mt_new(mrb);
    obj->mt = pmVar1;
    obj->iv = (iv_tbl *)0x0;
    if ((*(uint *)&o->tt & 0xff) == 9) {
      if (*(long *)&o[1].tt == 0) {
        obj->super = mrb->class_class;
      }
      else {
        obj->super = (RClass *)**(undefined8 **)&o[1].tt;
      }
    }
    else {
      c = (RClass *)o;
      if ((*(uint *)&o->tt & 0xff) == 0xc) {
        while ((*(uint *)&c->super->tt & 0xff) == 0xb) {
          c = c->super;
        }
        make_metaclass(mrb,c->super);
        obj->super = c->super->c;
      }
      else {
        obj->super = o->c;
        prepare_singleton_class(mrb,(RBasic *)obj);
      }
    }
    o->c = obj;
    mrb_field_write_barrier(mrb,o,(RBasic *)obj);
    mrb_field_write_barrier(mrb,(RBasic *)obj,o);
    mVar2 = mrb_obj_value(o);
    v._12_4_ = 0;
    v.value = (mrb_value_union)SUB128(mVar2._0_12_,0);
    v.tt = SUB124(mVar2._0_12_,8);
    mrb_obj_iv_set(mrb,(RObject *)obj,0,v);
    obj->flags = obj->flags | o->flags & 0x100000;
  }
  return;
}