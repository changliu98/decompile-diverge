void decrement_value(int *value)

{
  int *value_local;
  
  if (value != (int *)0x0) {
    *value = *value + -1;
  }
  return;
}