void __cdecl swap(float *min, float *max)
{
  int temp; // [rsp+0h] [rbp-14h]

  if ( *min > *max )
  {
    temp = *(_DWORD *)max;
    *max = *min;
    *(_DWORD *)min = temp;
  }
}