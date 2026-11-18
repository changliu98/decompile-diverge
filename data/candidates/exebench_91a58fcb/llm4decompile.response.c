void StrBracketMatch(char *in, int *CommaPositions, int *Nargs, int *ClosingBracketPos, int MaxCommaPoses)
{
  int BracketLevel, inpos, commapos;
  char QuoteType;

  BracketLevel = 0;
  commapos = 0;
  QuoteType = 0;
  for (inpos = 0; in[inpos] != 0; inpos++) {
    if (QuoteType) {
      if (in[inpos] == QuoteType && in[inpos-1] != '\\')
        QuoteType = 0;
      continue;
    }
    if (in[inpos] == '\'' || in[inpos] == '\"') {
      QuoteType = in[inpos];
      continue;
    }
    if (in[inpos] == '(') {
      BracketLevel++;
      if (BracketLevel == 1 && CommaPositions != NULL && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
        CommaPositions[commapos++] = inpos;
      continue;
    }
    if (in[inpos] == ')') {
      BracketLevel--;
      if (BracketLevel == 0)
        break;
      continue;
    }
    if (in[inpos] == ',' && BracketLevel == 1 && CommaPositions != NULL && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
      CommaPositions[commapos++] = inpos;
  }
  if (in[inpos] != 0) {
    if (CommaPositions != NULL && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
      CommaPositions[commapos++] = inpos;
    if (Nargs != NULL)
      *Nargs = commapos-1;
    if (ClosingBracketPos != NULL)
      *ClosingBracketPos = inpos;
  } else {
    if (Nargs != NULL)
      *Nargs = -1;
    if (ClosingBracketPos != NULL)
      *ClosingBracketPos = -1;
  }
}