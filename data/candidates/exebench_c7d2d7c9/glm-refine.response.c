void __cdecl passByPointer(int *x)
{
  // Initialize the dereferenced value to 4
  *x = 4;
  
  // Multiply the dereferenced value by 4 (4 * 4 = 16)
  *x *= 4;
}