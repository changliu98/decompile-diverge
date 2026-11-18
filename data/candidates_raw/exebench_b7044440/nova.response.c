void func0(struct Stack *stack) {
    int i = 0;
    while (i < MAX_SIZE) {
        stack->data[i] = stack->data[i + 1];
        i++;
    }
    stack->top = -1;
}