int escape(char *fmt,int percent,size_t *len)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  int value;
  char c;
  char *store;
  char *save;
  size_t *len_local;
  int percent_local;
  char *fmt_local;
  
  store = fmt;
  fmt_local = fmt;
  do {
    cVar1 = *fmt_local;
    if (cVar1 == '\0') {
      *store = '\0';
      *len = (long)store - (long)fmt;
      return 0;
    }
    if (cVar1 == '\\') {
      pcVar2 = fmt_local + 1;
      switch(fmt_local[1]) {
      case '\0':
        *store = '\\';
        store[1] = '\0';
        *len = (size_t)(store + (1 - (long)fmt));
        return 0;
      default:
        *store = *pcVar2;
        fmt_local = pcVar2;
        break;
      case '\'':
      case '\\':
        *store = *pcVar2;
        fmt_local = pcVar2;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        bVar3 = false;
        if (percent == 0) {
          bVar3 = *pcVar2 == '0';
        }
        c = '\x03';
        if (bVar3) {
          c = '\x04';
        }
        value = 0;
        fmt_local = pcVar2;
        while( true ) {
          bVar3 = false;
          if ((c != '\0') && (bVar3 = false, '/' < *fmt_local)) {
            bVar3 = *fmt_local < '8';
          }
          if (!bVar3) break;
          value = *fmt_local + -0x30 + value * 8;
          fmt_local = fmt_local + 1;
          c = c + -1;
        }
        fmt_local = fmt_local + -1;
        if ((percent == 0) || (value != 0x25)) {
          *store = (char)value;
        }
        else {
          *store = '%';
          store[1] = '%';
          store = store + 1;
        }
        break;
      case 'a':
        *store = '\a';
        fmt_local = pcVar2;
        break;
      case 'b':
        *store = '\b';
        fmt_local = pcVar2;
        break;
      case 'c':
        if (percent == 0) {
          *store = '\0';
          *len = (long)store - (long)fmt;
          return 1;
        }
        *store = 'c';
        fmt_local = pcVar2;
        break;
      case 'f':
        *store = '\f';
        fmt_local = pcVar2;
        break;
      case 'n':
        *store = '\n';
        fmt_local = pcVar2;
        break;
      case 'r':
        *store = '\r';
        fmt_local = pcVar2;
        break;
      case 't':
        *store = '\t';
        fmt_local = pcVar2;
        break;
      case 'v':
        *store = '\v';
        fmt_local = pcVar2;
      }
    }
    else {
      *store = cVar1;
    }
    fmt_local = fmt_local + 1;
    store = store + 1;
  } while( true );
}