void __cdecl func0(const char *message, char *out)
{
  char w; // [rsp+Fh] [rbp-21h]
  int j; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]

  for ( i = 0; message[i]; ++i )
  {
    w = message[i];
    if ( ((*__ctype_b_loc())[w] & 0x200) != 0 )
    {
      w = toupper(w);
    }
    else if ( ((*__ctype_b_loc())[w] & 0x100) != 0 )
    {
      w = tolower(w);
    }
    for ( j = 0; aAeiouaeiou[j]; ++j )
    {
      if ( w == aAeiouaeiou[j] )
      {
        if ( j < 10 )
          w += 2;
        break;
      }
    }
    out[i] = w;
  }
  out[i] = 0;
}