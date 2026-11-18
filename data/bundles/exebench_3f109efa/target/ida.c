void __cdecl ceasar(char *text, char offset)
{
  int j; // [rsp+0h] [rbp-14h]
  unsigned int i; // [rsp+4h] [rbp-10h]

  for ( i = 0; text[i]; ++i )
  {
    if ( text[i] > 64 && text[i] < 91 || text[i] > 96 && text[i] < 123 )
    {
      for ( j = 0; j < offset; ++j )
      {
        if ( text[i] == 90 )
        {
          text[i] = 65;
          --text[i];
        }
        if ( text[i] == 122 )
        {
          text[i] = 97;
          --text[i];
        }
        ++text[i];
      }
    }
  }
}