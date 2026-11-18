_Bool validateRegexSyntax(char *re)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char c;
  size_t i;
  _Bool lastWasQuantifier;
  _Bool lastWasPipe;
  _Bool hasAtom;
  _Bool charClassHasContent;
  _Bool escaped;
  _Bool inCharClass;
  int parenDepth;
  char *re_local;
  _Bool local_9;
  
  parenDepth = 0;
  bVar7 = false;
  bVar6 = false;
  bVar2 = false;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  i = 0;
  do {
    if (re[i] == '\0') {
      if ((((bVar6) || (bVar7)) || (parenDepth != 0)) || (bVar4)) {
        local_9 = false;
      }
      else {
        local_9 = true;
      }
      return local_9;
    }
    cVar1 = re[i];
    if (bVar6) {
      bVar6 = false;
      bVar5 = true;
      bVar4 = false;
      bVar3 = false;
    }
    else if (cVar1 == '\\') {
      bVar6 = true;
    }
    else if (bVar7) {
      if (cVar1 == ']') {
        if (!bVar2) {
          return false;
        }
        bVar7 = false;
        bVar5 = true;
        bVar4 = false;
        bVar3 = false;
      }
      else {
        bVar2 = true;
      }
    }
    else if (cVar1 == '[') {
      bVar7 = true;
      bVar2 = false;
    }
    else {
      if (cVar1 == ']') {
        return false;
      }
      if (cVar1 == '(') {
        parenDepth = parenDepth + 1;
        bVar5 = false;
        bVar4 = false;
        bVar3 = false;
      }
      else if (cVar1 == ')') {
        if ((parenDepth == 0) || (!bVar5)) {
          return false;
        }
        parenDepth = parenDepth + -1;
        bVar5 = true;
        bVar4 = false;
        bVar3 = false;
      }
      else if (cVar1 == '|') {
        if (!bVar5) {
          return false;
        }
        bVar5 = false;
        bVar4 = true;
        bVar3 = false;
      }
      else if (((cVar1 == '*') || (cVar1 == '+')) || (cVar1 == '?')) {
        if ((!bVar5) || (bVar3)) {
          return false;
        }
        bVar4 = false;
        bVar3 = true;
      }
      else {
        bVar5 = true;
        bVar4 = false;
        bVar3 = false;
      }
    }
    i = i + 1;
  } while( true );
}