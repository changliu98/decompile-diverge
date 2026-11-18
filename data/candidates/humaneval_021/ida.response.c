void __cdecl func0(float *numbers, int size)
{
  int i_0; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]
  float max; // [rsp+8h] [rbp-14h]
  float min; // [rsp+Ch] [rbp-10h]

  min = *numbers;
  max = *numbers;
  for ( i = 1; i < size; ++i )
  {
    if ( min > numbers[i] )
      min = numbers[i];
    if ( numbers[i] > max )
      max = numbers[i];
  }
  for ( i_0 = 0; i_0 < size; ++i_0 )
    numbers[i_0] = (float)(numbers[i_0] - min) / (float)(max - min);
}