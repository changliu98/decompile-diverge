void NearestNeighbor(int *index, float *array, float value, int arlength)
{
  int i;
  float bestcrit,crit;

  bestcrit = (array[0]-value)*(array[0]-value);
  *index = 0;
  for(i=1;i<arlength;i++) {
    crit = (array[i]-value)*(array[i]-value);
    if(crit < bestcrit) {
      bestcrit = crit;
      *index = i;
    }
  }
}