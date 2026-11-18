int *__cdecl func0(int *nums, int size)
{
  unsigned int v2; // eax
  int j_0; // [rsp+10h] [rbp-40h]
  int i_0; // [rsp+14h] [rbp-3Ch]
  int m; // [rsp+18h] [rbp-38h]
  int ma; // [rsp+18h] [rbp-38h]
  int j; // [rsp+1Ch] [rbp-34h]
  int length; // [rsp+20h] [rbp-30h]
  int sum; // [rsp+24h] [rbp-2Ch]
  int suma; // [rsp+24h] [rbp-2Ch]
  char w[12]; // [rsp+28h] [rbp-28h] BYREF
  int i; // [rsp+34h] [rbp-1Ch]
  int *sumdigit; // [rsp+38h] [rbp-18h]
  int sizea; // [rsp+44h] [rbp-Ch]
  int *numsa; // [rsp+48h] [rbp-8h]

  numsa = nums;
  sizea = size;
  sumdigit = (int *)malloc(4LL * size);
  for ( i = 0; i < sizea; ++i )
  {
    v2 = abs(numsa[i]);
    sprintf(w, "%d", v2);
    sum = 0;
    length = strlen(w);
    for ( j = 1; j < length; ++j )
      sum += w[j] - 48;
    if ( numsa[i] <= 0 )
      suma = sum - (w[0] - 48);
    else
      suma = sum + w[0] - 48;
    sumdigit[i] = suma;
  }
  for ( i_0 = 0; i_0 < sizea; ++i_0 )
  {
    for ( j_0 = 1; j_0 < sizea; ++j_0 )
    {
      if ( sumdigit[j_0 - 1] > sumdigit[j_0] )
      {
        m = sumdigit[j_0];
        sumdigit[j_0] = sumdigit[j_0 - 1];
        sumdigit[j_0 - 1] = m;
        ma = numsa[j_0];
        numsa[j_0] = numsa[j_0 - 1];
        numsa[j_0 - 1] = ma;
      }
    }
  }
  free(sumdigit);
  return numsa;
}