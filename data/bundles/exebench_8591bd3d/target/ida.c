char *__cdecl read_prefix(
        char *cx_0,
        int *isref,
        int *isarray,
        int *passin,
        int *passout,
        int *nullok,
        int *isretained,
        int *isreturn)
{
  *isref = 0;
  *passin = 0;
  *passout = 0;
  *nullok = 1;
  *isarray = 0;
  *isretained = 0;
  *isreturn = 0;
  while ( 1 )
  {
    switch ( *cx_0 )
    {
      case '<':
        *isref = 1;
        *passout = 1;
        goto LABEL_17;
      case '>':
        *isref = 1;
        *passin = 1;
        goto LABEL_17;
      case '&':
        *isref = 1;
        *passout = 1;
        *passin = 1;
        goto LABEL_17;
      case '+':
        *nullok = 0;
        goto LABEL_17;
      case ':':
        *isref = 1;
        *passout = 1;
        *nullok = 0;
        *isreturn = 1;
        goto LABEL_17;
      case '#':
        *isarray = 1;
        goto LABEL_17;
    }
    if ( *cx_0 != 33 )
      return cx_0;
    *isretained = 1;
LABEL_17:
    ++cx_0;
  }
}