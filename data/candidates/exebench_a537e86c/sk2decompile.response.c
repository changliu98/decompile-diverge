double dst_transform_push(double* stack, int* stack_top, double value) {
  if (*stack_top < 16) {
    stack[(*stack_top)++] = value;
  }
  return value;
}