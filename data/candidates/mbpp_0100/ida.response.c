int __cdecl func0(int num)
{
  int j; // [rsp+4h] [rbp-2Ch]
  int isPalindrome; // [rsp+8h] [rbp-28h]
  int len; // [rsp+Ch] [rbp-24h]
  char numstr[20]; // [rsp+10h] [rbp-20h] BYREF
  int i; // [rsp+24h] [rbp-Ch]
  int numa; // [rsp+28h] [rbp-8h]

  numa = num;
  for ( i = num + 1; i != 0x7FFFFFFF; ++i )
  {
    sprintf(numstr, "%d", (unsigned int)i);
    len = strlen(numstr);
    isPalindrome = 1;
    for ( j = 0; j < len / 2; ++j )
    {
      if ( numstr[j] != numstr[len - 1 - j] )
      {
        isPalindrome = 0;
        break;
      }
    }
    if ( isPalindrome )
      return i;
  }
  return -1;
}