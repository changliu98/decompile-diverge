void __cdecl func0(int *x, int size, int **out, int *out_size)
{
  char v4; // [rsp+7h] [rbp-39h]
  int temp; // [rsp+8h] [rbp-38h]
  int j; // [rsp+Ch] [rbp-34h]
  int i_0; // [rsp+10h] [rbp-30h]
  char has_even_digit; // [rsp+17h] [rbp-29h]
  int num; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]

  *out = (int *)malloc(4LL * size);
  *out_size = 0;
  for ( i = 0; i < size; ++i )
  {
    num = x[i];
    has_even_digit = num == 0;
    while ( 1 )
    {
      v4 = 0;
      if ( num > 0 )
        v4 = ~has_even_digit;
      if ( (v4 & 1) == 0 )
        break;
      if ( !(num % 2) )
        has_even_digit = 1;
      num /= 10;
    }
    if ( (has_even_digit & 1) == 0 )
      (*out)[(*out_size)++] = x[i];
  }
  for ( i_0 = 0; i_0 < *out_size - 1; ++i_0 )
  {
    for ( j = 0; j < *out_size - i_0 - 1; ++j )
    {
      if ( (*out)[j] > (*out)[j + 1] )
      {
        temp = (*out)[j];
        (*out)[j] = (*out)[j + 1];
        (*out)[j + 1] = temp;
      }
    }
  }
}