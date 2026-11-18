void maxind(double *segmentToAnalyze, int length, double *maximum, double *index)
{
  int i;

  *maximum = segmentToAnalyze[0];
  *index = 0.0;
  for (i=1; i<length; i++)
    {
      if (segmentToAnalyze[i] > *maximum)
 {
   *maximum = segmentToAnalyze[i];
   *index = (double)i * 0.001;
 }
    }
}