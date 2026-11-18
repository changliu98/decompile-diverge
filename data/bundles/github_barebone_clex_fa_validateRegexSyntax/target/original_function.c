static bool validateRegexSyntax(const char* re) {
  int parenDepth = 0;
  bool inCharClass = false;
  bool escaped = false;
  bool charClassHasContent = false;
  bool hasAtom = false;
  bool lastWasPipe = false;
  bool lastWasQuantifier = false;

  for (size_t i = 0; re[i] != '\0'; i++) {
    const char c = re[i];
    if (escaped) {
      escaped = false;
      hasAtom = true;
      lastWasPipe = false;
      lastWasQuantifier = false;
      continue;
    }
    if (c == '\\') {
      escaped = true;
      continue;
    }
    if (inCharClass) {
      if (c == ']') {
        if (!charClassHasContent) return false;
        inCharClass = false;
        hasAtom = true;
        lastWasPipe = false;
        lastWasQuantifier = false;
      } else {
        charClassHasContent = true;
      }
      continue;
    }

    if (c == '[') {
      inCharClass = true;
      charClassHasContent = false;
      continue;
    }
    if (c == ']') return false;

    if (c == '(') {
      parenDepth++;
      hasAtom = false;
      lastWasPipe = false;
      lastWasQuantifier = false;
      continue;
    }
    if (c == ')') {
      if (parenDepth == 0 || !hasAtom) return false;
      parenDepth--;
      hasAtom = true;
      lastWasPipe = false;
      lastWasQuantifier = false;
      continue;
    }

    if (c == '|') {
      if (!hasAtom) return false;
      hasAtom = false;
      lastWasPipe = true;
      lastWasQuantifier = false;
      continue;
    }

    if (c == '*' || c == '+' || c == '?') {
      if (!hasAtom || lastWasQuantifier) return false;
      lastWasPipe = false;
      lastWasQuantifier = true;
      continue;
    }

    hasAtom = true;
    lastWasPipe = false;
    lastWasQuantifier = false;
  }

  if (escaped || inCharClass || parenDepth != 0 || lastWasPipe) return false;
  return true;
}