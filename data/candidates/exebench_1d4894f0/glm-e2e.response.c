void stack4_replace_top(unsigned long *stack_ptr, unsigned long value) {
    *stack_ptr = (*stack_ptr & 0xFFFFFFFFFFFFFFF0UL) | value;
}