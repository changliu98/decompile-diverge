void collectgarbage(struct VM* vm) {
    int i;
    struct Object* obj;
    int type;
    int temp_type;

    // 1. Mark Phase
    for (i = 0; i < vm->root_count; i++) {
        mark(vm, vm->roots[i]);
    }

    // Call sweep_obj on the temporary root
    sweep_obj(vm, vm->temp);

    // 2. Sweep Phase
    for (i = 0; i < vm->obj_count; i++) {
        obj = (struct Object*)(vm->objects + (i * 16));

        // Extract type if marked (bit 0 is set)
        if ((int8_t)obj->flags & 0x1) {
            type = (int8_t)obj->flags >> 2;
        } else {
            type = 0;
        }

        // If type == 1, skip this object (continue)
        if (type == 1) {
            continue;
        }

        // Check if bit 1 is NOT set (object is unmarked)
        if (((int8_t)obj->flags ^ -1) & 0x2) {
            
            // Extract type again into temp_type
            if ((int8_t)obj->flags & 0x1) {
                temp_type = (int8_t)obj->flags >> 2;
            } else {
                temp_type = 0;
            }

            // If temp_type == 10 and finalizer exists, call it
            if (temp_type == 10 && vm->finalizer != NULL) {
                vm->finalizer(vm, obj);
            }

            // Add object to free list
            obj->flags = 5; // 0b00000101
            obj->next = vm->free_list;
            vm->free_list = obj;
        } else {
            // Object is marked, clear the mark bit (bit 1)
            obj->flags &= ~0x2; // 0xFFFFFFFD
        }
    }
}