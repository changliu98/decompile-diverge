void __cdecl prepare_singleton_class(mrb_state *mrb, RBasic *o)
{
  RClass *class_class; // rcx
  RBasic *c; // [rsp+20h] [rbp-20h]
  RBasic *sc; // [rsp+28h] [rbp-18h]
  mrb_value v5; // 0:rcx.8,8:r8d.4

  if ( (unsigned __int8)*((_DWORD *)o->c + 4) != 12 )
  {
    sc = mrb_obj_alloc(mrb, mrb_vtype::MRB_TT_SCLASS, mrb->class_class);
    *((_DWORD *)sc + 4) = (((*((_DWORD *)sc + 4) >> 11) | 0x20000) << 11) | *((_DWORD *)sc + 4) & 0x7FF;
    sc[1].gcnext = (RBasic *)mt_new(mrb);
    sc[1].c = 0LL;
    if ( (unsigned __int8)*((_DWORD *)o + 4) == 9 )
    {
      if ( *((_QWORD *)&o[1] + 2) )
        class_class = (RClass *)**((_QWORD **)&o[1] + 2);
      else
        class_class = mrb->class_class;
      *((_QWORD *)&sc[1] + 2) = class_class;
    }
    else if ( (unsigned __int8)*((_DWORD *)o + 4) == 12 )
    {
      for ( c = o; (unsigned __int8)*(_DWORD *)(*((_QWORD *)&c[1] + 2) + 16LL) == 11; c = (RBasic *)*((_QWORD *)&c[1] + 2) )
        ;
      make_metaclass(mrb, *((RClass **)&c[1] + 2));
      *((_QWORD *)&sc[1] + 2) = **((_QWORD **)&c[1] + 2);
    }
    else
    {
      *((_QWORD *)&sc[1] + 2) = o->c;
      prepare_singleton_class(mrb, sc);
    }
    o->c = (RClass *)sc;
    mrb_field_write_barrier(mrb, o, sc);
    mrb_field_write_barrier(mrb, sc, o);
    v5 = mrb_obj_value(o);
    mrb_obj_iv_set(mrb, (RObject *)sc, 0, v5);
    *((_DWORD *)sc + 4) = (((*((_DWORD *)o + 4) >> 11) & 0x100000 | (*((_DWORD *)sc + 4) >> 11)) << 11) | *((_DWORD *)sc + 4) & 0x7FF;
  }
}