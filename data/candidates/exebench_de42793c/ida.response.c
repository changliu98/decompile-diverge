int __cdecl conv_hstring(char *string, unsigned int *num)
{
  int v2; // edx
  int v3; // edx
  bool v5; // [rsp+1h] [rbp-15h]
  int pos; // [rsp+2h] [rbp-14h]

  pos = 0;
  *num = 0;
  while ( 1 )
  {
    if ( string[pos] >= 48 && string[pos] <= 57 || (v5 = 0, string[pos] >= 97) && (v5 = 0, string[pos] <= 102) )
      v5 = pos < 9;
    if ( !v5 )
      break;
    if ( string[pos] < 48 || string[pos] > 57 )
    {
      v3 = pos++;
      *num = string[v3] - 97 + 16 * *num + 10;
    }
    else
    {
      v2 = pos++;
      *num = string[v2] - 48 + 16 * *num;
    }
  }
  return pos;
}