// Converts an array of integers representing base-10 digits into a single integer.
// This is an implementation of Horner's method.
int __cdecl digits_to_int(int *digits, int count)
{
  int value = 0;
  
  for (int i = 0; i < count; ++i)
  {
    value = digits[i] + 10 * value;
  }
  
  return value;
}