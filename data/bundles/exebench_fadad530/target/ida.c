void __cdecl ToIUPAC(char *seq, int is_aseq)
{
  if ( is_aseq )
  {
    while ( *seq )
    {
      if ( !strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq)
        && *seq != 32
        && *seq != 46
        && *seq != 95
        && *seq != 45
        && *seq != 126 )
      {
        *seq = 78;
      }
      ++seq;
    }
  }
  else
  {
    while ( *seq )
    {
      if ( !strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) )
        *seq = 78;
      ++seq;
    }
  }
}