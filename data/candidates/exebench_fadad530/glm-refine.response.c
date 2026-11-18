void __cdecl ToIUPAC(char *seq, int is_aseq)
{
  while ( *seq )
  {
    char c = *seq;
    int is_valid_iupac = strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", c) != NULL;
    int is_valid_aseq_char = (c == 32 || c == 46 || c == 95 || c == 45 || c == 126);

    if ( !is_valid_iupac && (!is_aseq || !is_valid_aseq_char) )
    {
      *seq = 'N'; // ASCII 78
    }
    ++seq;
  }
}