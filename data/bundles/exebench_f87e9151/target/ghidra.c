void NearestNeighbor(int *index,float *array,float value,int arlength)

{
  float fVar1;
  float crit;
  float bestcrit;
  int i;
  int arlength_local;
  float value_local;
  float *array_local;
  int *index_local;
  
  bestcrit = (*array - value) * (*array - value);
  *index = 0;
  for (i = 1; i < arlength; i = i + 1) {
    fVar1 = (array[i] - value) * (array[i] - value);
    if (fVar1 < bestcrit) {
      *index = i;
      bestcrit = fVar1;
    }
  }
  return;
}