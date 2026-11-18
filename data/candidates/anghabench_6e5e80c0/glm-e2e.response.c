void* adjust_stack_addr(void* ptr, int offset) {
    return ptr + offset * 8;
}