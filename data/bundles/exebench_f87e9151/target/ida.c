void __cdecl NearestNeighbor(int *index, float *array, float value, int arlength)
{
  float crita; // [rsp+0h] [rbp-24h]
  float crit; // [rsp+0h] [rbp-24h]
  float bestcrit; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]

  bestcrit = (float)(*array - value) * (float)(*array - value);
  *index = 0;
  for ( i = 1; i < arlength; ++i )
  {
    crita = array[i] - value;
    crit = crita * crita;
    if ( bestcrit > crit )
    {
      bestcrit = crit;
      *index = i;
    }
  }
}