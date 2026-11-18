
static char *read_prefix(char *cx, int *isref, int *isarray,
  int *passin, int *passout, int *nullok, int *isretained,
  int *isreturn)
{
  *isref = 0;
  *passin = 0;
  *passout = 0;
  *nullok = 1;
  *isarray = 0;
  *isretained = 0;
  *isreturn = 0;
  while (1) {
    if (*cx == '<') {
      *isref = 1;
      *passout = 1;
    }
    else if (*cx == '>') {
      *isref = 1;
      *passin = 1;
    }
    else if (*cx == '&') {
      *isref = 1;
      *passout = 1;
      *passin = 1;
    }
    else if (*cx == '+') {
      *nullok = 0;
    }
    else if (*cx == ':') {
      *isref = 1;
      *passout = 1;
      *nullok = 0;
      *isreturn = 1;
    }
    else if (*cx == '#') {
      *isarray = 1;
    }
    else if (*cx == '!') {
      *isretained = 1;
    }
    else {
      break;
    }
    cx++;
  }
  return cx;
}
