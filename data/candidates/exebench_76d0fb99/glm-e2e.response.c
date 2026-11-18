void stack4_push(unsigned long *stack, unsigned long value) {
    *stack = (*stack << 4) | value;
}