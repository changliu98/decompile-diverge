char zhalfstr(char *s)

{
  char cVar1;
  bool bVar2;
  char cVar3;
  int back;
  int nonzero;
  int index;
  char lastchar;
  char outchar;
  char nextchar;
  char curchar;
  char *s_local;
  
  curchar = '0';
  lastchar = '0';
  index = -1;
  bVar2 = false;
  back = 0;
  while (curchar != '\0') {
    cVar1 = s[(long)index + 1];
    cVar3 = (char)(cVar1 + -0x30 >> 1) + (curchar & 1U) * '\x05' + '0';
    s[((long)index + 1) - (long)back] = cVar3;
    if ((cVar3 != '0') || (bVar2)) {
      bVar2 = true;
    }
    else {
      back = back + 1;
    }
    if (curchar != '\0') {
      lastchar = curchar;
    }
    index = index + 1;
    curchar = cVar1;
  }
  if (index == back) {
    *s = '0';
    s[1] = '\0';
  }
  else {
    s[(long)index - (long)back] = '\0';
  }
  return lastchar;
}