// This function searches an array of integers for the first negative value.
// If a negative value is found, it is returned immediately.
// If no negative values are present, or if the array is empty, it returns 0.
int __cdecl find_first_negative(int *array, int length)
{
  int i; // Loop counter

  for ( i = 0; i < length; ++i )
  {
    if ( array[i] < 0 )
      return array[i]; // Return the first negative integer encountered
  }
  return 0; // Return 0 if no negative integers are found
}