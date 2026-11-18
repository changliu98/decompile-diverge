void sub3(double *target_array, double *source_array)
{
  // Subtract the value pointed to by a2 from the value pointed to by a1
  *target_array -= *source_array;
  // Subtract the second element of a2 from the second element of a1
  target_array[1] -= source_array[1];
  // Subtract the third element of a2 from the third element of a1
  target_array[2] -= source_array[2];
}