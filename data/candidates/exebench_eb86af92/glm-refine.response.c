void __cdecl maxind(double *segmentToAnalyze, int length, double *maximum, double *index)
{
  // Initialize the maximum with the first element and set the index to 0.0
  *maximum = segmentToAnalyze[0];
  *index = 0.0;

  // Iterate through the rest of the array to find the maximum value and its index
  for (int i = 1; i < length; ++i)
  {
    if (segmentToAnalyze[i] > *maximum)
    {
      *maximum = segmentToAnalyze[i];
      // Cast the integer index 'i' to a double and store it
      *index = (double)i;
    }
  }
}