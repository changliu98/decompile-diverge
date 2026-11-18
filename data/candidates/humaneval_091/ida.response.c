int __cdecl func0(const char *S)
{
  int i; // [rsp+8h] [rbp-18h]
  int sum; // [rsp+Ch] [rbp-14h]
  int isi; // [rsp+10h] [rbp-10h]
  int isstart; // [rsp+14h] [rbp-Ch]

  isstart = 1;
  isi = 0;
  sum = 0;
  for ( i = 0; S[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[S[i]] & 0x2000) != 0 && isi )
    {
      isi = 0;
      ++sum;
    }
    if ( S[i] == 73 && isstart )
    {
      isi = 1;
    }
    else if ( ((*__ctype_b_loc())[S[i]] & 0x2000) == 0 )
    {
      isi = 0;
    }
    if ( ((*__ctype_b_loc())[S[i]] & 0x2000) == 0 )
      isstart = 0;
    if ( S[i] == 46 || S[i] == 63 || S[i] == 33 )
      isstart = 1;
  }
  return sum;
}