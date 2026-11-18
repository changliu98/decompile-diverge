char *__cdecl func0(char *s)
{
  char temp; // [rsp+7h] [rbp-19h]
  int i_0; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int length; // [rsp+10h] [rbp-10h]
  int nletter; // [rsp+14h] [rbp-Ch]

  nletter = 0;
  length = strlen(s);
  for ( i = 0; i < length; ++i )
  {
    if ( ((*__ctype_b_loc())[(unsigned __int8)s[i]] & 0x400) != 0 )
    {
      if ( ((*__ctype_b_loc())[(unsigned __int8)s[i]] & 0x100) != 0 )
      {
        s[i] = tolower((unsigned __int8)s[i]);
      }
      else if ( ((*__ctype_b_loc())[(unsigned __int8)s[i]] & 0x200) != 0 )
      {
        s[i] = toupper((unsigned __int8)s[i]);
      }
    }
    else
    {
      ++nletter;
    }
  }
  if ( nletter == length )
  {
    for ( i_0 = 0; i_0 < length / 2; ++i_0 )
    {
      temp = s[i_0];
      s[i_0] = s[length - i_0 - 1];
      s[length - i_0 - 1] = temp;
    }
  }
  return s;
}