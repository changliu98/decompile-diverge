void pattern_check_unclosed_captures(Pattern_State *ps)

{
  char *pcVar1;
  size_t sVar2;
  char *pat;
  int captures;
  int i;
  Pattern_State *ps_local;
  
  i = 1;
  while( true ) {
    if (ps->capture_count <= i) {
      return;
    }
    if (ps->captures[i].size == -1) break;
    i = i + 1;
  }
  captures = 0;
  pat = ps->pattern_base;
  while (pcVar1 = ps->pattern_base, sVar2 = strlen(ps->pattern_base), pat < pcVar1 + sVar2) {
    if (*pat == '%') {
      pat = pat + 2;
    }
    else {
      if ((*pat == '(') && (captures = captures + 1, captures == i)) break;
      pat = pat + 1;
    }
  }
  pattern_set_error(ps,PATTERN_ERR_UNCLOSED_CAPTURE,(long)pat - (long)ps->pattern_base);
  return;
}