bool __cdecl validateRegexSyntax(const char *re)
{
  char c; // [rsp+1h] [rbp-29h]
  size_t i; // [rsp+2h] [rbp-28h]
  bool lastWasQuantifier; // [rsp+10h] [rbp-1Ah]
  bool lastWasPipe; // [rsp+11h] [rbp-19h]
  bool hasAtom; // [rsp+12h] [rbp-18h]
  bool charClassHasContent; // [rsp+13h] [rbp-17h]
  bool escaped; // [rsp+14h] [rbp-16h]
  bool inCharClass; // [rsp+15h] [rbp-15h]
  int parenDepth; // [rsp+16h] [rbp-14h]

  parenDepth = 0;
  inCharClass = 0;
  escaped = 0;
  charClassHasContent = 0;
  hasAtom = 0;
  lastWasPipe = 0;
  lastWasQuantifier = 0;
  for ( i = 0LL; re[i]; ++i )
  {
    c = re[i];
    if ( escaped )
    {
      escaped = 0;
      hasAtom = 1;
      lastWasPipe = 0;
      lastWasQuantifier = 0;
    }
    else if ( c == 92 )
    {
      escaped = 1;
    }
    else if ( inCharClass )
    {
      if ( c == 93 )
      {
        if ( !charClassHasContent )
          return 0;
        inCharClass = 0;
        hasAtom = 1;
        lastWasPipe = 0;
        lastWasQuantifier = 0;
      }
      else
      {
        charClassHasContent = 1;
      }
    }
    else
    {
      switch ( c )
      {
        case '[':
          inCharClass = 1;
          charClassHasContent = 0;
          break;
        case ']':
          return 0;
        case '(':
          ++parenDepth;
          hasAtom = 0;
          lastWasPipe = 0;
          lastWasQuantifier = 0;
          break;
        case ')':
          if ( !parenDepth || !hasAtom )
            return 0;
          --parenDepth;
          hasAtom = 1;
          lastWasPipe = 0;
          lastWasQuantifier = 0;
          break;
        case '|':
          if ( !hasAtom )
            return 0;
          hasAtom = 0;
          lastWasPipe = 1;
          lastWasQuantifier = 0;
          break;
        case '*':
        case '+':
        case '?':
          if ( !hasAtom || lastWasQuantifier )
            return 0;
          lastWasPipe = 0;
          lastWasQuantifier = 1;
          break;
        default:
          hasAtom = 1;
          lastWasPipe = 0;
          lastWasQuantifier = 0;
          break;
      }
    }
  }
  return !escaped && !inCharClass && !parenDepth && !lastWasPipe;
}