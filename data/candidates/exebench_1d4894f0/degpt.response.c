void stack4_replace_top(unsigned_long *stack_pointer, unsigned_long entry_value)
{
    // Clear the lower 4 bits of the value pointed to by s
    // and set them to the value of e (assuming e fits in 4 bits)
    *stack_pointer = *stack_pointer & 0xfffffffffffffff0 | entry_value;
}