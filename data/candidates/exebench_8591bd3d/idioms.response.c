char *read_prefix(char *cx, int *isref, int *isarray, int *passin, int *passout, int *nullok, int *isretained, int *isreturn)
{
  *isref = 0;
  *passin = 0;
  *passout = 0;
  *nullok = 1;
  *isarray = 0;
  *isretained = 0;
  *isreturn = 0;
  while (1) {
    switch (*cx) {
    case '<':
      *isref = 1;
      *passout = 1;
      break;
    case '>':
      *isref = 1;
      *passin = 1;
      break;
    case '&':
      *isref = 1;
      *passout = 1;
      *passin = 1;
      break;
    case '+':
      *nullok = 0;
      break;
    case ':':
      *isref = 1;
      *passout = 1;
      *nullok = 0;
      *isreturn = 1;
      break;
    case '#':
      *isarray = 1;
      break;
    case '!':
      *isretained = 1;
      break;
    default:
      return cx;
    }
    cx++;
  }
}