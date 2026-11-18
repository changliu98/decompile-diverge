void __cdecl right_shift_str(char *p, int n)
{
  char temp; // [rsp+1h] [rbp-21h]
  char *q; // [rsp+2h] [rbp-20h]
  int length_of_str; // [rsp+Ah] [rbp-18h]
  int j; // [rsp+Eh] [rbp-14h]
  int i; // [rsp+12h] [rbp-10h]

  length_of_str = 0;
  for ( q = p; *q; ++q )
    ++length_of_str;
  for ( j = 0; j < n; ++j )
  {
    temp = p[length_of_str - 1];
    for ( i = length_of_str - 1; i > 0; --i )
      p[i] = p[i - 1];
    *p = temp;
  }
}