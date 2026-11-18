#include <math.h>

#include <stdlib.h>

void maxind(double * segmentToAnalyze, int length, double *maximum, double *index)
{
  int i=0;


  *maximum = segmentToAnalyze[0];
  *index = 0;
  for(i=1;i<length;i++)
    {
      if(segmentToAnalyze[i]>*maximum)
        {
   *maximum = segmentToAnalyze[i];
   *index = 1.0*i;
        }
    }
}
