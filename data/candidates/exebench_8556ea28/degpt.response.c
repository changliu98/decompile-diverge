void sum(int value, int *result)
{
  // Check if the output pointer is valid before dereferencing
  if (result != NULL) {
    // Add the value of c to the integer pointed to by output
    *result += value;
  }
}