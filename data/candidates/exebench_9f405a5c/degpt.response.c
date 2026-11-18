// Copies the first four elements from array b to array a
void copyvector(float *destination, float *source)
{
  *destination = *source;      // Copy the first element (index 0)
  destination[1] = source[1];  // Copy the second element (index 1)
  destination[2] = source[2];  // Copy the third element (index 2)
  destination[3] = source[3];  // Copy the fourth element (index 3)
}