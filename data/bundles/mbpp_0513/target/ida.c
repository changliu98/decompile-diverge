char **__cdecl func0(int *test_tup, int size, char *K)
{
  int v3; // ecx
  int i; // [rsp+8h] [rbp-28h]
  int j; // [rsp+Ch] [rbp-24h]
  char **res; // [rsp+10h] [rbp-20h]

  res = (char **)malloc(16LL * size);
  j = 0;
  for ( i = 0; i < size; ++i )
  {
    asprintf(&res[j], "%d", (unsigned int)test_tup[i]);
    v3 = j + 1;
    j += 2;
    res[v3] = K;
  }
  return res;
}