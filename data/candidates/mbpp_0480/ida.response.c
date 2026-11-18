char __cdecl func0(const char *str1)
{
  int i_0; // [rsp+Ch] [rbp-424h]
  int i; // [rsp+10h] [rbp-420h]
  int length; // [rsp+14h] [rbp-41Ch]
  char ch_0; // [rsp+1Bh] [rbp-415h]
  int max; // [rsp+1Ch] [rbp-414h]
  int ctr[256]; // [rsp+20h] [rbp-410h] BYREF
  int ASCII_SIZE; // [rsp+424h] [rbp-Ch]
  const char *str1a; // [rsp+428h] [rbp-8h]

  str1a = str1;
  ASCII_SIZE = 256;
  memset(ctr, 0, sizeof(ctr));
  max = -1;
  ch_0 = 0;
  length = strlen(str1a);
  for ( i = 0; i < length; ++i )
    ++ctr[str1a[i]];
  for ( i_0 = 0; i_0 < length; ++i_0 )
  {
    if ( max < ctr[str1a[i_0]] )
    {
      max = ctr[str1a[i_0]];
      ch_0 = str1a[i_0];
    }
  }
  return ch_0;
}