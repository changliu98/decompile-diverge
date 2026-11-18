void expand(char *compacted,char *expanded)

{
  int ee;
  int e;
  char *expanded_local;
  char *compacted_local;
  
  if ((((*compacted < '0') || ('9' < *compacted)) || (compacted[2] < '0')) ||
     (('9' < compacted[2] || (compacted[2] < *compacted)))) {
    if (((*compacted < 'A') || (('Z' < *compacted || (compacted[2] < 'A')))) ||
       (('Z' < compacted[2] || (compacted[2] < *compacted)))) {
      if (((('`' < *compacted) && (*compacted < '{')) && ('`' < compacted[2])) &&
         ((compacted[2] < '{' && (*compacted <= compacted[2])))) {
        ee = 0;
        for (e = (int)*compacted; e <= compacted[2]; e = e + 1) {
          expanded[ee] = (char)e;
          ee = ee + 1;
        }
        expanded[ee] = '\0';
      }
    }
    else {
      ee = 0;
      for (e = (int)*compacted; e <= compacted[2]; e = e + 1) {
        expanded[ee] = (char)e;
        ee = ee + 1;
      }
      expanded[ee] = '\0';
    }
  }
  else {
    ee = 0;
    for (e = (int)*compacted; e <= compacted[2]; e = e + 1) {
      expanded[ee] = (char)e;
      ee = ee + 1;
    }
    expanded[ee] = '\0';
  }
  return;
}