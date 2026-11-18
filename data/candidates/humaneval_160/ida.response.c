int __cdecl func0(const char **operato, const int *operand, int operato_size, int operand_size)
{
  __int64 v4; // rcx
  int v5; // edx
  __int64 v6; // rcx
  int v7; // edx
  int result; // [rsp+14h] [rbp-3Ch]
  int i_2; // [rsp+18h] [rbp-38h]
  int i_1; // [rsp+1Ch] [rbp-34h]
  int i_0; // [rsp+20h] [rbp-30h]
  int i; // [rsp+24h] [rbp-2Ch]
  int *posto; // [rsp+28h] [rbp-28h]
  int *num; // [rsp+30h] [rbp-20h]

  num = (int *)malloc(4LL * operand_size);
  posto = (int *)malloc(4LL * operand_size);
  for ( i = 0; i < operand_size; ++i )
  {
    num[i] = operand[i];
    posto[i] = i;
  }
  for ( i_0 = 0; i_0 < operato_size; ++i_0 )
  {
    if ( !strcmp(operato[i_0], "**") )
    {
      while ( posto[posto[i_0]] != posto[i_0] )
        posto[i_0] = posto[posto[i_0]];
      while ( posto[posto[i_0 + 1]] != posto[i_0 + 1] )
        posto[i_0 + 1] = posto[posto[i_0 + 1]];
      num[posto[i_0]] = (int)pow((double)num[posto[i_0]], (double)num[posto[i_0 + 1]]);
      posto[i_0 + 1] = posto[i_0];
    }
  }
  for ( i_1 = 0; i_1 < operato_size; ++i_1 )
  {
    if ( !strcmp(operato[i_1], "*") || !strcmp(operato[i_1], "//") )
    {
      while ( posto[posto[i_1]] != posto[i_1] )
        posto[i_1] = posto[posto[i_1]];
      while ( posto[posto[i_1 + 1]] != posto[i_1 + 1] )
        posto[i_1 + 1] = posto[posto[i_1 + 1]];
      if ( !strcmp(operato[i_1], "*") )
      {
        v4 = posto[i_1];
        v5 = num[v4] * num[posto[i_1 + 1]];
      }
      else
      {
        v4 = posto[i_1];
        v5 = num[v4] / num[posto[i_1 + 1]];
      }
      num[v4] = v5;
      posto[i_1 + 1] = posto[i_1];
    }
  }
  for ( i_2 = 0; i_2 < operato_size; ++i_2 )
  {
    if ( !strcmp(operato[i_2], "+") || !strcmp(operato[i_2], "-") )
    {
      while ( posto[posto[i_2]] != posto[i_2] )
        posto[i_2] = posto[posto[i_2]];
      while ( posto[posto[i_2 + 1]] != posto[i_2 + 1] )
        posto[i_2 + 1] = posto[posto[i_2 + 1]];
      if ( !strcmp(operato[i_2], "+") )
      {
        v6 = posto[i_2];
        v7 = num[v6] + num[posto[i_2 + 1]];
      }
      else
      {
        v6 = posto[i_2];
        v7 = num[v6] - num[posto[i_2 + 1]];
      }
      num[v6] = v7;
      posto[i_2 + 1] = posto[i_2];
    }
  }
  result = *num;
  free(num);
  free(posto);
  return result;
}