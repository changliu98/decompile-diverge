void __cdecl reverse(char *rline)
{
  char temp; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  for ( i = 0; rline[i]; ++i )
    ;
  ia = i - 1;
  if ( rline[ia] == 10 )
    --ia;
  for ( j = 0; j < ia; ++j )
  {
    temp = rline[j];
    rline[j] = rline[ia];
    rline[ia--] = temp;
  }
}