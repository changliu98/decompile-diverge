bool __cdecl func0(char **l1, char **l2, int size1, int size2)
{
  char *v4; // rcx
  int v5; // eax
  char *v6; // rcx
  int v7; // eax
  char *v8; // rcx
  int v9; // eax
  int i_2; // [rsp+Ch] [rbp-9C4h]
  int j_1; // [rsp+10h] [rbp-9C0h]
  int i_1; // [rsp+14h] [rbp-9BCh]
  int j_0; // [rsp+18h] [rbp-9B8h]
  int i_0; // [rsp+1Ch] [rbp-9B4h]
  char *ordered_l2[100]; // [rsp+20h] [rbp-9B0h]
  char *ordered_l1[100]; // [rsp+340h] [rbp-690h]
  int index2; // [rsp+668h] [rbp-368h]
  int index1; // [rsp+66Ch] [rbp-364h]
  int k; // [rsp+670h] [rbp-360h]
  bool is_unique; // [rsp+677h] [rbp-359h]
  int j; // [rsp+678h] [rbp-358h]
  int i; // [rsp+67Ch] [rbp-354h]
  char *common_elements[100]; // [rsp+680h] [rbp-350h]
  int common_elements_size; // [rsp+9ACh] [rbp-24h]
  int size2a; // [rsp+9B0h] [rbp-20h]
  int size1a; // [rsp+9B4h] [rbp-1Ch]
  char **l2a; // [rsp+9B8h] [rbp-18h]
  char **l1a; // [rsp+9C0h] [rbp-10h]

  l1a = l1;
  l2a = l2;
  size1a = size1;
  size2a = size2;
  common_elements_size = 0;
  for ( i = 0; i < size1a; ++i )
  {
    for ( j = 0; j < size2a; ++j )
    {
      if ( !strcmp(l1a[i], l2a[j]) )
      {
        is_unique = 1;
        for ( k = 0; k < common_elements_size; ++k )
        {
          if ( !strcmp(common_elements[k], l1a[i]) )
          {
            is_unique = 0;
            break;
          }
        }
        if ( is_unique )
        {
          v4 = l1a[i];
          v5 = common_elements_size++;
          common_elements[v5] = v4;
        }
      }
    }
  }
  index1 = 0;
  index2 = 0;
  for ( i_0 = 0; i_0 < size1a; ++i_0 )
  {
    for ( j_0 = 0; j_0 < common_elements_size; ++j_0 )
    {
      if ( !strcmp(l1a[i_0], common_elements[j_0]) )
      {
        v6 = l1a[i_0];
        v7 = index1++;
        ordered_l1[v7] = v6;
      }
    }
  }
  for ( i_1 = 0; i_1 < size2a; ++i_1 )
  {
    for ( j_1 = 0; j_1 < common_elements_size; ++j_1 )
    {
      if ( !strcmp(l2a[i_1], common_elements[j_1]) )
      {
        v8 = l2a[i_1];
        v9 = index2++;
        ordered_l2[v9] = v8;
      }
    }
  }
  if ( index1 != index2 )
    return 0;
  for ( i_2 = 0; i_2 < index1; ++i_2 )
  {
    if ( strcmp(ordered_l1[i_2], ordered_l2[i_2]) )
      return 0;
  }
  return 1;
}