_Bool matchbrack(char *pat,int sc,int folded)

{
  _Bool _Var1;
  int iVar2;
  int hi;
  int lo;
  _Bool compl;
  int pc;
  int folded_local;
  int sc_local;
  char *pat_local;
  
  _Var1 = false;
  if ((*pat == '!') || (pat_local = pat, *pat == '^')) {
    _Var1 = true;
    pat_local = pat + 1;
  }
  if (*pat_local == ']') {
    if (sc == 0x5d) {
      return (_Bool)(_Var1 ^ 1);
    }
    pat_local = pat_local + 1;
  }
  else if (*pat_local == '-') {
    if (sc == 0x2d) {
      return (_Bool)(_Var1 ^ 1);
    }
    pat_local = pat_local + 1;
  }
  pc = (int)pat_local[-1];
  do {
    while( true ) {
      if (*pat_local == ']') {
        return _Var1;
      }
      if ((*pat_local == '-') && (pat_local[1] != ']')) break;
      pc = utf8get(&pat_local);
      if ((pc == sc) || (pc == folded)) {
        return (_Bool)(_Var1 ^ 1);
      }
    }
    pat_local = pat_local + 1;
    iVar2 = utf8get(&pat_local);
  } while (((sc < pc) || (iVar2 < sc)) && ((folded < pc || (iVar2 < folded))));
  return (_Bool)(_Var1 ^ 1);
}