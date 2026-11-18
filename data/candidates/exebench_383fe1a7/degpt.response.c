// Assigns the value of DAT_00102004 to the 10th element of the array pointed to by a
// Returns the value of the 10th element of the array pointed to by a
float foo(float *array_ptr)
{
  array_ptr[9] = CONSTANT_VALUE;
  return array_ptr[9];
}