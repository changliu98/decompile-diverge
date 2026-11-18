acts as a pointer to an array or struct
int __cdecl foo(int condition, int *array_ptr)
{
  if (condition == 9)
  {
    // If condition is 9, zero out the second element (index 1)
    array_ptr[1] = 0;
  }
  else
  {
    // Otherwise, zero out the first element (index 0)
    array_ptr[0] = 0;
  }
  
  return 3;
}