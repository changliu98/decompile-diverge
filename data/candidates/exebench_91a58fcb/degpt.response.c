void StrBracketMatch(char *in,int *CommaPositions,int *Nargs,int *ClosingBracketPos,
                    int MaxCommaPoses)

{
  char QuoteType;
  int commapos;
  int inpos;
  int BracketLevel;
  int MaxCommaPoses_local;
  int *ClosingBracketPos_local;
  int *Nargs_local;
  int *CommaPositions_local;
  char *in_local;
  
  BracketLevel = 0;
  commapos = 0;
  QuoteType = '\0';
  for (inpos = 0; in[inpos] != '\0'; inpos = inpos + 1) {
    if (QuoteType == '\0') {
      if ((in[inpos] == '\'') || (in[inpos] == '\"')) {
        QuoteType = in[inpos];
      }
      else if (in[inpos] == '(') {
        BracketLevel = BracketLevel + 1;
        if (((BracketLevel == 1) && (CommaPositions != (int *)0x0)) &&
           ((MaxCommaPoses < 0 || (commapos < MaxCommaPoses)))) {
          CommaPositions[commapos] = inpos;
          commapos = commapos + 1;
        }
      }
      else if (in[inpos] == ')') {
        BracketLevel = BracketLevel + -1;
        if (BracketLevel == 0) break;
      }
      else if ((((in[inpos] == ',') && (BracketLevel == 1)) && (CommaPositions != (int *)0x0)) &&
              ((MaxCommaPoses < 0 || (commapos < MaxCommaPoses)))) {
        CommaPositions[commapos] = inpos;
        commapos = commapos + 1;
      }
    }
    else if ((in[inpos] == QuoteType) && (in[inpos + -1] != '\\')) {
      QuoteType = '\0';
    }
  }
  if (in[inpos] == '\0') {
    if (Nargs != (int *)0x0) {
      *Nargs = -1;
    }
    if (ClosingBracketPos != (int *)0x0) {
      *ClosingBracketPos = -1;
    }
  }
  else {
    if ((CommaPositions != (int *)0x0) && ((MaxCommaPoses < 0 || (commapos < MaxCommaPoses)))) {
      CommaPositions[commapos] = inpos;
      commapos = commapos + 1;
    }
    if (Nargs != (int *)0x0) {
      *Nargs = commapos + -1;
    }
    if (ClosingBracketPos != (int *)0x0) {
      *ClosingBracketPos = inpos;
    }
  }
  return;
}