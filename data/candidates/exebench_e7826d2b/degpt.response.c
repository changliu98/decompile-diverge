void foo(int *array)
{
  // Iterate 24 times (0x18 in hexadecimal)
  for (int index = 0; index < 0x18; index++) {
    // Increment the value at the current index
    array[index]++;
  }
}