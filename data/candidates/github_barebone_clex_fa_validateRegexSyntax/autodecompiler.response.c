int validateRegexSyntax(char *re)
{
 int parenDepth = 0;
 int inCharClass = 0;
 int escaped = 0;
 int charClassHasContent = 0;
 int hasAtom = 0;
 int lastWasPipe = 0;
 int lastWasQuantifier = 0;
 size_t i;
 char c;
 char valid;

 for (i = 0;; i++) {
  if (!re[i]) {
   break;
  }
  c = re[i];
  if (escaped & 1) {
   escaped = 0;
   hasAtom = 1;
   lastWasPipe = 0;
   lastWasQuantifier = 0;
   continue;
  }
  if (c == '\\') {
   escaped = 1;
   continue;
  }
  if (inCharClass & 1) {
   if (c == ']') {
    if (!(charClassHasContent & 1)) {
     valid = 0;
     goto end;
    }
    inCharClass = 0;
    hasAtom = 1;
    lastWasPipe = 0;
    lastWasQuantifier = 0;
   } else {
    charClassHasContent = 1;
   }
   continue;
  }
  if (c == '[') {
   inCharClass = 1;
   charClassHasContent = 0;
   continue;
  }
  if (c == ']') {
   valid = 0;
   goto end;
  }
  if (c == '(') {
   parenDepth++;
   hasAtom = 0;
   lastWasPipe = 0;
   lastWasQuantifier = 0;
   continue;
  }
  if (c == ')') {
   if (parenDepth == 0 || !(hasAtom & 1)) {
    valid = 0;
    goto end;
   }
   parenDepth--;
   hasAtom = 1;
   lastWasPipe = 0;
   lastWasQuantifier = 0;
   continue;
  }
  if (c == '|') {
   if (!(hasAtom & 1)) {
    valid = 0;
    goto end;
   }
   hasAtom = 0;
   lastWasPipe = 1;
   lastWasQuantifier = 0;
   continue;
  }
  if (c == '*' || c == '+' || c == '?') {
   if (!(hasAtom & 1) || (lastWasQuantifier & 1)) {
    valid = 0;
    goto end;
   }
   lastWasPipe = 0;
   lastWasQuantifier = 1;
   continue;
  }
  hasAtom = 1;
  lastWasPipe = 0;
  lastWasQuantifier = 0;
 }
 if ((escaped & 1) || (inCharClass & 1) || (parenDepth != 0) ||
     (lastWasPipe & 1)) {
  valid = 0;
  goto end;
 }
 valid = 1;
end:
 return valid & 1;
}