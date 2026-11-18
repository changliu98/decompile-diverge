void __cdecl func0(const char *str, char *out)
{
  char w; // [rsp+7h] [rbp-19h]
  int i; // [rsp+8h] [rbp-18h]
  int length; // [rsp+Ch] [rbp-14h]

  length = strlen(str);
  for ( i = 0; i < length; ++i )
  {
    w = str[i];
    if ( w < 97 || w > 122 )
    {
      if ( w >= 65 && w <= 90 )
        w += 32;
    }
    else
    {
      w -= 32;
    }
    out[i] = w;
  }
  out[length] = 0;
}