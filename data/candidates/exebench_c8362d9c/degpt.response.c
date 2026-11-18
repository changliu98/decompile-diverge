char * parse_fmt(char *fmt,int *type,int *size)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  char *s;
  int *size_local;
  int *type_local;
  char *fmt_local;
  
  fmt_local = fmt;
  do {
    while( true ) {
      bVar3 = false;
      if (*fmt_local != '\0') {
        bVar3 = *fmt_local != '%';
      }
      if (!bVar3) break;
      fmt_local = fmt_local + 1;
    }
    iVar1 = (int)fmt_local;
    iVar2 = (int)fmt;
    if (*fmt_local == '%') {
      if (fmt_local[1] == '%') {
        *size = (iVar1 - iVar2) + 1;
        *type = -1;
        return fmt_local + 2;
      }
      if (fmt_local[1] == 'v') {
        *type = 0xf;
        *size = iVar1 - iVar2;
        return fmt_local + 2;
      }
    }
    if (*fmt_local == '\0') {
      *type = -1;
      *size = iVar1 - iVar2;
      return fmt_local;
    }
  } while( true );
}