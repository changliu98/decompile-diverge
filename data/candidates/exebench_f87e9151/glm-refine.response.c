void __cdecl NearestNeighbor(int *index, float *array, float value, int arlength)
{
  float bestcrit = (array[0] - value) * (array[0] - value);
  *index = 0;

  for (int i = 1; i < arlength; ++i)
  {
    float diff = array[i] - value;
    float crit = diff * diff;
    
    if (bestcrit > crit)
    {
      bestcrit = crit;
      *index = i;
    }
  }
}