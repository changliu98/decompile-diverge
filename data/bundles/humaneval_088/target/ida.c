void __cdecl func0(int *array, int size, int **out_array, int *out_size)
{
  int temp_0; // [rsp+8h] [rbp-38h]
  int temp; // [rsp+Ch] [rbp-34h]
  int j; // [rsp+10h] [rbp-30h]
  int i_0; // [rsp+14h] [rbp-2Ch]
  int shouldSortAscending; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]

  *out_size = size;
  if ( size )
  {
    *out_array = (int *)malloc(4LL * size);
    if ( !*out_array )
      exit(1);
    for ( i = 0; i < size; ++i )
      (*out_array)[i] = array[i];
    shouldSortAscending = (array[size - 1] + *array) % 2 == 1;
    for ( i_0 = 0; i_0 < size - 1; ++i_0 )
    {
      for ( j = i_0 + 1; j < size; ++j )
      {
        if ( shouldSortAscending )
        {
          if ( (*out_array)[i_0] > (*out_array)[j] )
          {
            temp = (*out_array)[i_0];
            (*out_array)[i_0] = (*out_array)[j];
            (*out_array)[j] = temp;
          }
        }
        else if ( (*out_array)[i_0] < (*out_array)[j] )
        {
          temp_0 = (*out_array)[i_0];
          (*out_array)[i_0] = (*out_array)[j];
          (*out_array)[j] = temp_0;
        }
      }
    }
  }
  else
  {
    *out_array = 0LL;
  }
}