RClass* prepare_singleton_class(mrb_state *mrb, RObject *obj) {
    // If the object is already a class (type 0xc), return early
    if (get_type((RBasic *)obj) == 0xc) {
        return NULL;
    }

    // Allocate a new class object (type 0xc)
    RClass *sclass = mrb_obj_alloc(mrb, 0xc, (RClass *)mrb);
    
    // Set a specific flag bit (likely FL_SINGLETON)
    set_flag_bit((RBasic *)sclass, 0x20000);

    // Initialize method table and superclass
    sclass->mt = mt_new(mrb);
    sclass->super = NULL;

    RObject *target = obj;
    int obj_type = get_type((RBasic *)obj);

    if (obj_type == 0x9) { // Type 0x9: Likely standard objects/instances
        if (target->c == NULL) {
            sclass->c = mrb->c;
        } else {
            sclass->c = (RClass *)target->c->c;
        }
    } else if (obj_type == 0xc) { // Type 0xc: Class or Module
        target = obj;
        
        // Traverse up the metaclass chain if already a metaclass (type 0xb)
        while (get_type((RBasic *)target->c) == 0xb) {
            target = (RObject *)target->c;
        }
        
        // Create the metaclass
        make_metaclass(mrb, (RClass *)target);
        
        // Assign the metaclass chain
        sclass->c = (RClass *)target->c->c;
    } else { // Other types
        sclass->c = (RClass *)obj->c;
        prepare_singleton_class(mrb, (RObject *)sclass);
    }

    // Link the singleton class back to the object
    obj->c = (RClass *)sclass;

    // Write barriers for garbage collector tracking
    mrb_field_write_barrier(mrb, (RBasic *)mrb, (RBasic *)obj);
    mrb_field_write_barrier(mrb, (RBasic *)mrb, (RBasic *)sclass);

    // Set an instance variable (likely storing the attached object)
    // The return value of mrb_obj_value is split across rax and edx
    uint64_t val_lo;
    uint32_t val_hi;
    RObject *obj_val = mrb_obj_value(obj);
    val_lo = (uint64_t)obj_val;
    val_hi = 0; // xor %edx, %edx implies 0 for the upper 32 bits
    
    mrb_obj_iv_set(mrb, sclass, val_lo, val_hi, 0);

    // Propagate another flag from the object to the singleton class
    uint32_t obj_flags = obj->flags;
    uint32_t mask = (obj_flags >> 11) & 0x100000;
    set_flag_bit((RBasic *)sclass, mask);

    return sclass;
}