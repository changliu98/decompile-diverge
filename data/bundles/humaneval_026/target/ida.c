int *__cdecl func0(int *numbers, int size, int *new_size)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int j_1; // [rsp+Ch] [rbp-64h]
  int in_has2_0; // [rsp+10h] [rbp-60h]
  int num_0; // [rsp+14h] [rbp-5Ch]
  int i_0; // [rsp+18h] [rbp-58h]
  int j_0; // [rsp+1Ch] [rbp-54h]
  int in_has1; // [rsp+20h] [rbp-50h]
  int j; // [rsp+24h] [rbp-4Ch]
  int in_has2; // [rsp+28h] [rbp-48h]
  int num; // [rsp+2Ch] [rbp-44h]
  int i; // [rsp+30h] [rbp-40h]
  int out_count; // [rsp+34h] [rbp-3Ch]
  int has2_count; // [rsp+38h] [rbp-38h]
  int has1_count; // [rsp+3Ch] [rbp-34h]
  int *has2; // [rsp+40h] [rbp-30h]
  int *has1; // [rsp+48h] [rbp-28h]
  int *out; // [rsp+50h] [rbp-20h]

  out = (int *)malloc(4LL * size);
  has1 = (int *)calloc(size, 4uLL);
  has2 = (int *)calloc(size, 4uLL);
  has1_count = 0;
  has2_count = 0;
  out_count = 0;
  for ( i = 0; i < size; ++i )
  {
    num = numbers[i];
    in_has2 = 0;
    for ( j = 0; j < has2_count; ++j )
    {
      if ( has2[j] == num )
      {
        in_has2 = 1;
        break;
      }
    }
    if ( !in_has2 )
    {
      in_has1 = 0;
      for ( j_0 = 0; j_0 < has1_count; ++j_0 )
      {
        if ( has1[j_0] == num )
        {
          in_has1 = 1;
          break;
        }
      }
      if ( in_has1 )
      {
        v3 = has2_count++;
        has2[v3] = num;
      }
      else
      {
        v4 = has1_count++;
        has1[v4] = num;
      }
    }
  }
  for ( i_0 = 0; i_0 < size; ++i_0 )
  {
    num_0 = numbers[i_0];
    in_has2_0 = 0;
    for ( j_1 = 0; j_1 < has2_count; ++j_1 )
    {
      if ( has2[j_1] == num_0 )
      {
        in_has2_0 = 1;
        break;
      }
    }
    if ( !in_has2_0 )
    {
      v5 = out_count++;
      out[v5] = num_0;
    }
  }
  *new_size = out_count;
  free(has1);
  free(has2);
  return out;
}