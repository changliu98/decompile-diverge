int64_t njs_vmcode_array(struct njs_vm_s *vm, njs_vmcode_array_t *code) {
    njs_array_t *array;
    uint8_t *ptr;
    int32_t length;

    array = njs_array_alloc(vm, 0, code->length, 8);
    
    if (array != NULL) {
        if (code->init != 0) {
            ptr = array->start;
            length = array->length;
            
            // Initialize array elements
            while (length != 0) {
                *ptr = 7; // Assign type/value 7
                ptr += 16; // Move to next element (size 16 bytes)
                length--;
            }
        } else {
            array->length = 0;
        }
        
        njs_set_array(vm, array);
        return 0x20; // 32
    }
    
    return -1; // 0xffffffffffffffff
}