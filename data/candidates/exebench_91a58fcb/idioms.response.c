void StrBracketMatch(char *in, int *CommaPositions, int *Nargs, int *ClosingBracketPos, int MaxCommaPoses)
{
  int inpos = 0;
  int commapos = 0;
  int BracketLevel = 0;
  char QuoteType = '\0';
  while (in[inpos])
  {
    if (QuoteType)
    {
      if (in[inpos] == QuoteType && in[inpos - 1] != '\\')
        QuoteType = '\0';
    }
    else
    {
      switch (in[inpos])
      {
        case '\'':
        case '"':
          QuoteType = in[inpos];
          break;
        case '(':
          BracketLevel++;
          if (CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
            CommaPositions[commapos++] = inpos;
          break;
        case ')':
          BracketLevel--;
          if (!BracketLevel)
            goto end;
          break;
        case ',':
          if (BracketLevel == 1 && CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
            CommaPositions[commapos++] = inpos;
          break;
      }
    }
    inpos++;
  }
end:
  if (in[inpos] == '\0')
  {
    if (Nargs)
      *Nargs = -1;
    if (ClosingBracketPos)
      *ClosingBracketPos = -1;
  }
  else
  {
    if (CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
      CommaPositions[commapos++] = inpos;
    if (Nargs)
      *Nargs = commapos - 1;
    if (ClosingBracketPos)
      *ClosingBracketPos = inpos;
  }
}