// Multiplies the value pointed to by 'a' by 2 using bitwise left shift
// Divides the value pointed to by 'b' by 2 using integer division
// Returns the sum of the modified values pointed to by 'a' and 'b'
int foo(int *value_a,int *value_b,int unused_param)
{
  *value_a = *value_a << 1;
  *value_b = *value_b / 2;
  return *value_a + *value_b;
}