char *__cdecl func0(const char *test_str)
{
  int v1; // eax
  int v2; // eax
  int idx; // [rsp+4h] [rbp-41Ch]
  int j; // [rsp+8h] [rbp-418h]
  int i; // [rsp+Ch] [rbp-414h]
  char dig[1024]; // [rsp+10h] [rbp-410h] BYREF
  const char *test_stra; // [rsp+418h] [rbp-8h]

  test_stra = test_str;
  i = 0;
  j = 0;
  for ( idx = 0; test_stra[idx]; ++idx )
  {
    if ( ((*__ctype_b_loc())[test_stra[idx]] & 0x800) != 0 )
    {
      v1 = j++;
      dig[v1] = test_stra[idx];
    }
    else
    {
      v2 = i++;
      func0_res[v2] = test_stra[idx];
    }
  }
  dig[j] = 0;
  func0_res[i] = 0;
  strcat(func0_res, dig);
  return func0_res;
}