struct njs_value_t njs_vmcode_typeof(void *vm, uint8_t *value, void *retval) {
    uint8_t type = *value;
    
    // Look up the type string from the table based on the byte value
    struct njs_string_t *type_str = &njs_vmcode_typeof_types[type];
    
    // Copy the 16-byte string representation (pointer + length) into the return value
    struct njs_value_t *out = (struct njs_value_t *)retval;
    out->data1 = (uint64_t)type_str->str;
    out->data2 = type_str->length;
    
    // Return a 24-byte (0x18) struct. 
    // The compiler optimizes returning this struct by placing a pointer in rdi 
    // and returning the size 0x18 in eax, which is a common ABI optimization.
    struct njs_value_t result;
    return result;
}