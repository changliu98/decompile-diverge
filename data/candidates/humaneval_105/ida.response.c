void __cdecl func0(int *arr, int size, char ***out, int *out_size)
{
  int v4; // ecx
  bool v5; // [rsp+3h] [rbp-7Dh]
  int temp; // [rsp+4h] [rbp-7Ch]
  int j; // [rsp+8h] [rbp-78h]
  int ja; // [rsp+8h] [rbp-78h]
  int i; // [rsp+Ch] [rbp-74h]
  int ia; // [rsp+Ch] [rbp-74h]
  int ib; // [rsp+Ch] [rbp-74h]
  char *names[10]; // [rsp+10h] [rbp-70h] BYREF
  int *out_sizea; // [rsp+60h] [rbp-20h]
  char ***outa; // [rsp+68h] [rbp-18h]
  int sizea; // [rsp+74h] [rbp-Ch]
  int *arra; // [rsp+78h] [rbp-8h]

  arra = arr;
  sizea = size;
  outa = out;
  out_sizea = out_size;
  memcpy(names, &off_3D90, sizeof(names));
  for ( i = 0; i < sizea - 1; ++i )
  {
    for ( j = 0; j < sizea - i - 1; ++j )
    {
      if ( arra[j] > arra[j + 1] )
      {
        temp = arra[j];
        arra[j] = arra[j + 1];
        arra[j + 1] = temp;
      }
    }
  }
  *out_sizea = 0;
  for ( ia = sizea - 1; ia >= 0; --ia )
  {
    if ( arra[ia] >= 1 && arra[ia] <= 9 )
      ++*out_sizea;
  }
  *outa = (char **)malloc(8LL * *out_sizea);
  ib = sizea - 1;
  ja = 0;
  while ( 1 )
  {
    v5 = 0;
    if ( ib >= 0 )
      v5 = ja < *out_sizea;
    if ( !v5 )
      break;
    if ( arra[ib] >= 1 && arra[ib] <= 9 )
    {
      v4 = ja++;
      (*outa)[v4] = names[arra[ib]];
    }
    --ib;
  }
}