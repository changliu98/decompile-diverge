int __cdecl func0(char *strr)
{
  int i; // [rsp+0h] [rbp-18h]
  int summ; // [rsp+4h] [rbp-14h]

  summ = 0;
  for ( i = 0; strr[i]; ++i )
    summ += strr[i] - 97 + 1;
  if ( summ % 26 )
    return summ % 26 + 96;
  else
    return 122;
}