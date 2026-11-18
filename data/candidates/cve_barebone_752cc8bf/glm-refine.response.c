void __cdecl prepare_singleton_class(mrb_state *mrb, RBasic *o) {
    // Check if the object's class is already a singleton class (MRB_TT_SCLASS = 12)
    if (((RClass*)o->c)->flags & 0xFF != MRB_TT_SCLASS) {
        // Allocate a new singleton class
        RObject *sc = (RObject*)mrb_obj_alloc(mrb, MRB_TT_SCLASS, mrb->class_class);
        
        // Set the FL_SINGLETON flag (0x20000 << 11 = 0x10000000)
        sc->flags |= 0x10000000;
        
        // Initialize method table and super class
        sc->iv_ptr = mt_new(mrb);
        sc->super = nullptr;
        
        // Determine the superclass of the singleton class based on the object's type
        uint32_t obj_type = o->flags & 0xFF;
        if (obj_type == MRB_TT_CLASS) {
            // For classes, the singleton's super is the class's class (metaclass)
            RObject *obj_as_obj = (RObject*)o;
            sc->super = obj_as_obj->super ? *(RClass**)obj_as_obj->super : mrb->class_class;
        } else if (obj_type == MRB_TT_SCLASS) {
            // For singleton classes, traverse up the chain to find the original class
            RBasic *c = o;
            while (((RObject*)c)->super && ((RClass*)((RObject*)c)->super)->flags & 0xFF == MRB_TT_ICLASS) {
                c = (RBasic*)((RObject*)c)->super;
            }
            make_metaclass(mrb, ((RObject*)c)->super);
            sc->super = *(RClass**)((RObject*)c)->super;
        } else {
            // For other objects, the singleton's super is the object's class
            sc->super = o->c;
            prepare_singleton_class(mrb, (RBasic*)sc);
        }
        
        // Link the singleton class to the object
        o->c = (RClass*)sc;
        mrb_field_write_barrier(mrb, o, sc);
        mrb_field_write_barrier(mrb, sc, o);
        
        // Set the object as the attached instance variable (key 0) of the singleton class
        mrb_value v = mrb_obj_value(o);
        mrb_obj_iv_set(mrb, sc, 0, v);
        
        // Inherit frozen flag (0x100000 << 11 = 0x80000000) from the object to the singleton class
        sc->flags |= (o->flags & 0x80000000);
    }
}