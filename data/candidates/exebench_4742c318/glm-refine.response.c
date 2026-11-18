float __cdecl mayorDif(float *arrayLineal)
{
  float mayor = 0.0f;
  
  // Iterate through the array until a 0.0 terminator is found
  for (int i = 0; arrayLineal[i + 1] != 0.0f; ++i)
  {
    // Calculate the absolute difference between adjacent elements
    float diff = std::abs(arrayLineal[i] - arrayLineal[i + 1]);
    
    // Update the maximum difference if the current one is larger
    if (diff > mayor)
    {
      mayor = diff;
    }
  }
  
  return mayor;
}