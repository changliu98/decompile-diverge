char *__cdecl func0(const char *S)
{
  int v1; // eax
  int i; // [rsp+10h] [rbp-10h]
  int j; // [rsp+14h] [rbp-Ch]

  j = 0;
  for ( i = 0; i < strlen(S); ++i )
  {
    if ( ((*__ctype_b_loc())[S[i]] & 8) != 0 )
    {
      v1 = j++;
      func0_result[v1] = S[i];
    }
  }
  func0_result[j] = 0;
  return func0_result;
}