void iadd(int *stack_array, int *stack_pointer, int value_to_add)
{
    // Decrement the stack pointer to pop the top element
    *stack_pointer = *stack_pointer - 1;
    // Add the second operand to the first operand and store the result in the first operand's position
    stack_array[*stack_pointer] += stack_array[*stack_pointer + 1];
}