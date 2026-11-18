void __cdecl StrBracketMatch(
        const char *in,
        int *CommaPositions,
        int *Nargs,
        int *ClosingBracketPos,
        int MaxCommaPoses)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char QuoteType; // [rsp+1h] [rbp-31h]
  int commapos; // [rsp+2h] [rbp-30h]
  int inpos; // [rsp+6h] [rbp-2Ch]
  int BracketLevel; // [rsp+Ah] [rbp-28h]

  BracketLevel = 0;
  inpos = 0;
  commapos = 0;
  QuoteType = 0;
  while ( in[inpos] )
  {
    if ( QuoteType )
    {
      if ( in[inpos] == QuoteType && in[inpos - 1] != 92 )
        QuoteType = 0;
    }
    else
    {
      switch ( in[inpos] )
      {
        case '\'':
        case '"':
          QuoteType = in[inpos];
          break;
        case '(':
          if ( ++BracketLevel == 1 && CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses) )
          {
            v5 = commapos++;
            CommaPositions[v5] = inpos;
          }
          break;
        case ')':
          if ( !--BracketLevel )
            goto LABEL_28;
          break;
        default:
          if ( in[inpos] == 44 && BracketLevel == 1 && CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses) )
          {
            v6 = commapos++;
            CommaPositions[v6] = inpos;
          }
          break;
      }
    }
    ++inpos;
  }
LABEL_28:
  if ( in[inpos] )
  {
    if ( CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses) )
    {
      v7 = commapos++;
      CommaPositions[v7] = inpos;
    }
    if ( Nargs )
      *Nargs = commapos - 1;
    if ( ClosingBracketPos )
      *ClosingBracketPos = inpos;
  }
  else
  {
    if ( Nargs )
      *Nargs = -1;
    if ( ClosingBracketPos )
      *ClosingBracketPos = -1;
  }
}