int INDMAXVAL(float *array, int imin, int imax)
{
 int i;
 int ind;

 ind = imin;
 for(i=imin+1; i<=imax; i++)
  if(array[i] > array[ind]) ind = i;

 return ind;
}