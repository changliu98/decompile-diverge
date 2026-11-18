void __cdecl expand(char *compacted, char *expanded)
{
  int ee; // [rsp+0h] [rbp-18h]
  int eea; // [rsp+0h] [rbp-18h]
  int eeb; // [rsp+0h] [rbp-18h]
  int e; // [rsp+4h] [rbp-14h]
  int ea; // [rsp+4h] [rbp-14h]
  int eb; // [rsp+4h] [rbp-14h]

  if ( *compacted < 48 || *compacted > 57 || compacted[2] < 48 || compacted[2] > 57 || *compacted > compacted[2] )
  {
    if ( *compacted < 65 || *compacted > 90 || compacted[2] < 65 || compacted[2] > 90 || *compacted > compacted[2] )
    {
      if ( *compacted >= 97
        && *compacted <= 122
        && compacted[2] >= 97
        && compacted[2] <= 122
        && *compacted <= compacted[2] )
      {
        eb = *compacted;
        eeb = 0;
        while ( eb <= compacted[2] )
          expanded[eeb++] = eb++;
        expanded[eeb] = 0;
      }
    }
    else
    {
      ea = *compacted;
      eea = 0;
      while ( ea <= compacted[2] )
        expanded[eea++] = ea++;
      expanded[eea] = 0;
    }
  }
  else
  {
    e = *compacted;
    ee = 0;
    while ( e <= compacted[2] )
      expanded[ee++] = e++;
    expanded[ee] = 0;
  }
}