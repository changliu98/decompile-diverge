int foo(int threshold, int *array_ptr)
{
  // If p is 9, set the second element of the array pointed to by q to 0
  if (threshold == 9) {
    array_ptr[1] = 0;
  }
  // Otherwise, set the first element of the array pointed to by q to 0
  else {
    *array_ptr = 0;
  }
  // Return the constant value 3
  return 3;
}