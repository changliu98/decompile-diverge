char __cdecl func0(char *str1)
{
  int v1; // eax
  int i_0; // [rsp+Ch] [rbp-524h]
  char c; // [rsp+13h] [rbp-51Dh]
  int i; // [rsp+14h] [rbp-51Ch]
  int length; // [rsp+18h] [rbp-518h]
  int idx; // [rsp+1Ch] [rbp-514h]
  char char_order[256]; // [rsp+20h] [rbp-510h]
  int ctr[256]; // [rsp+120h] [rbp-410h] BYREF
  char *str1a; // [rsp+520h] [rbp-10h]

  str1a = str1;
  memset(ctr, 0, sizeof(ctr));
  idx = 0;
  length = strlen(str1a);
  for ( i = 0; i < length; ++i )
  {
    c = str1a[i];
    if ( !ctr[c] )
    {
      v1 = idx++;
      char_order[v1] = c;
    }
    ++ctr[c];
  }
  for ( i_0 = 0; i_0 < idx; ++i_0 )
  {
    if ( ctr[char_order[i_0]] == 1 )
      return char_order[i_0];
  }
  return 0;
}