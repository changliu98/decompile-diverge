bool __cdecl func0(const char *str1, const char *str2)
{
  int i; // [rsp+Ch] [rbp-24h]
  int M; // [rsp+10h] [rbp-20h]
  int N; // [rsp+14h] [rbp-1Ch]

  N = strlen(str1);
  M = strlen(str2);
  if ( N % M )
    return 0;
  for ( i = 0; i < N; ++i )
  {
    if ( str1[i] != str2[i % M] )
      return 0;
  }
  return 1;
}