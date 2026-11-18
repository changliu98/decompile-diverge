static _Bool validateRegexSyntax(char *re)
{
  int parenDepth = 0;
  int inCharClass = 0;
  int escaped = 0;
  int charClassHasContent = 0;
  int hasAtom = 0;
  int lastWasPipe = 0;
  int lastWasQuantifier = 0;
  for (char *c = re; *c != '\0'; c++)
  {
    if (escaped)
    {
      escaped = 0;
      hasAtom = 1;
      lastWasPipe = 0;
      lastWasQuantifier = 0;
    }
    else if (*c == '\\')
    {
      escaped = 1;
    }
    else if (inCharClass)
    {
      if (*c == ']')
      {
        if (!charClassHasContent)
        {
          return 0;
        }
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
      if (*c == '[')
      {
        inCharClass = 1;
        charClassHasContent = 0;
      }
      else if (*c == ']')
      {
        return 0;
      }
      else if (*c == '(')
      {
        parenDepth++;
        hasAtom = 0;
        lastWasPipe = 0;
        lastWasQuantifier = 0;
      }
      else if (*c == ')')
      {
        if (parenDepth == 0 || !hasAtom)
        {
          return 0;
        }
        parenDepth--;
        hasAtom = 1;
        lastWasPipe = 0;
        lastWasQuantifier = 0;
      }
      else if (*c == '|')
      {
        if (!hasAtom)
        {
          return 0;
        }
        hasAtom = 0;
        lastWasPipe = 1;
        lastWasQuantifier = 0;
      }
      else if (*c == '*' || *c == '+' || *c == '?')
      {
        if (!hasAtom || lastWasQuantifier)
        {
          return 0;
        }
        lastWasPipe = 0;
        lastWasQuantifier = 1;
      }
      else
      {
        hasAtom = 1;
        lastWasPipe = 0;
        lastWasQuantifier = 0;
      }
    }
  }
  if (escaped || inCharClass || parenDepth != 0 || lastWasPipe)
  {
    return 0;
  }
  return 1;
}