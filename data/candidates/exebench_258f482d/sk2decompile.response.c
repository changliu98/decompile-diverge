void iadd(int *stack, int *sp, int arg) {
  int a;
  a = stack[*sp];
  (*sp)--;
  stack[*sp] += a;
}