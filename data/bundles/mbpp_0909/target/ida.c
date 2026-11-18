int __cdecl func0(int num)
{
  int i; // [rsp+10h] [rbp-30h]
  char temp; // [rsp+17h] [rbp-29h]
  int len; // [rsp+18h] [rbp-28h]
  int x; // [rsp+1Ch] [rbp-24h]
  char rev_str[12]; // [rsp+20h] [rbp-20h] BYREF
  char num_str[12]; // [rsp+2Ch] [rbp-14h] BYREF
  int numa; // [rsp+38h] [rbp-8h]

  numa = num;
  for ( x = num - 1; x > 0; --x )
  {
    sprintf(num_str, "%d", (unsigned int)x);
    strcpy(rev_str, num_str);
    len = strlen(rev_str);
    for ( i = 0; i < len / 2; ++i )
    {
      temp = rev_str[i];
      rev_str[i] = rev_str[len - 1 - i];
      rev_str[len - 1 - i] = temp;
    }
    if ( !strcmp(num_str, rev_str) )
      return x;
  }
  return 0;
}