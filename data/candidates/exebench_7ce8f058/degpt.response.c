// Snaps each component of the vector to the nearest integer by truncating the decimal part.
void SnapVector(float *vector)
{
  // Truncate the x-component to an integer and cast back to float
  vector[0] = (float)(int)vector[0];
  // Truncate the y-component to an integer and cast back to float
  vector[1] = (float)(int)vector[1];
  // Truncate the z-component to an integer and cast back to float
  vector[2] = (float)(int)vector[2];
}