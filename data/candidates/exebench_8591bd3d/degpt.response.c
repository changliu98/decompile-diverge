char * read_prefix(char *cx,int *isref,int *isarray,int *passin,int *passout,int *nullok,
                  int *isretained,int *isreturn)

{
  int *nullok_local;
  int *passout_local;
  int *passin_local;
  int *isarray_local;
  int *isref_local;
  char *cx_local;
  
  *isref = 0;
  *passin = 0;
  *passout = 0;
  *nullok = 1;
  *isarray = 0;
  *isretained = 0;
  *isreturn = 0;
  cx_local = cx;
  do {
    if (*cx_local == '<') {
      *isref = 1;
      *passout = 1;
    }
    else if (*cx_local == '>') {
      *isref = 1;
      *passin = 1;
    }
    else if (*cx_local == '&') {
      *isref = 1;
      *passout = 1;
      *passin = 1;
    }
    else if (*cx_local == '+') {
      *nullok = 0;
    }
    else if (*cx_local == ':') {
      *isref = 1;
      *passout = 1;
      *nullok = 0;
      *isreturn = 1;
    }
    else if (*cx_local == '#') {
      *isarray = 1;
    }
    else {
      if (*cx_local != '!') {
        return cx_local;
      }
      *isretained = 1;
    }
    cx_local = cx_local + 1;
  } while( true );
}