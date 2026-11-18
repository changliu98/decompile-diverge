char *__cdecl func0(const char *a, const char *b)
{
  double numb; // [rsp+8h] [rbp-48h]
  double numa; // [rsp+10h] [rbp-40h]
  int i_0; // [rsp+18h] [rbp-38h]
  int i; // [rsp+1Ch] [rbp-34h]
  char *b_modified; // [rsp+20h] [rbp-30h]
  char *a_modified; // [rsp+28h] [rbp-28h]
  char *end; // [rsp+30h] [rbp-20h] BYREF
  const char *ba; // [rsp+38h] [rbp-18h]
  const char *aa; // [rsp+40h] [rbp-10h]

  aa = a;
  ba = b;
  a_modified = strdup(a);
  b_modified = strdup(b);
  for ( i = 0; a_modified[i]; ++i )
  {
    if ( a_modified[i] == 44 )
      a_modified[i] = 46;
  }
  for ( i_0 = 0; b_modified[i_0]; ++i_0 )
  {
    if ( b_modified[i_0] == 44 )
      b_modified[i_0] = 46;
  }
  numa = strtod(a_modified, &end);
  if ( *end || (numb = strtod(b_modified, &end), *end) )
  {
    free(a_modified);
    free(b_modified);
    return "Invalid input";
  }
  else
  {
    free(a_modified);
    free(b_modified);
    if ( numa == numb )
    {
      return "None";
    }
    else if ( numa <= numb )
    {
      return (char *)ba;
    }
    else
    {
      return (char *)aa;
    }
  }
}