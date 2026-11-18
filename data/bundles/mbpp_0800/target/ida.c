void __cdecl func0(char *text, char *result)
{
  int v2; // ecx
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  i = 0;
  j = 0;
  while ( text[i] )
  {
    if ( ((*__ctype_b_loc())[(unsigned __int8)text[i]] & 0x2000) == 0 )
    {
      v2 = j++;
      result[v2] = text[i];
    }
    ++i;
  }
  result[j] = 0;
}