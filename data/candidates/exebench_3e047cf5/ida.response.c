void __cdecl ToRNA(char *seq)
{
  while ( *seq )
  {
    if ( *seq == 84 )
    {
      *seq = 85;
    }
    else if ( *seq == 116 )
    {
      *seq = 117;
    }
    ++seq;
  }
}