char * parse_content_length(char *buffer,char *end,int *length)

{
  char *pcVar1;
  bool bVar2;
  int size;
  char *p;
  int number;
  int *length_local;
  char *end_local;
  char *buffer_local;
  
  p = buffer;
  while( true ) {
    bVar2 = false;
    if ((((p < end) && (bVar2 = true, *p != ' ')) && (bVar2 = true, *p != '\t')) &&
       (((*p != '\r' || (bVar2 = true, p[1] != '\n')) &&
        ((bVar2 = false, *p == '\n' && (bVar2 = true, p[1] != ' ')))))) {
      bVar2 = p[1] == '\t';
    }
    if (!bVar2) break;
    p = p + 1;
  }
  if (p != end) {
    size = 0;
    number = 0;
    while( true ) {
      bVar2 = false;
      if ((p < end) && (bVar2 = false, '/' < *p)) {
        bVar2 = *p < ':';
      }
      if (!bVar2) break;
      number = number * 10 + (int)*p + -0x30;
      if (number < 0) {
        return (char *)0x0;
      }
      size = size + 1;
      p = p + 1;
    }
    if ((p != end) && (size != 0)) {
      while( true ) {
        bVar2 = false;
        if ((p < end) &&
           ((((bVar2 = true, *p != ' ' && (bVar2 = true, *p != '\t')) && (bVar2 = false, *p == '\n')
             ) && (bVar2 = true, p[1] != ' ')))) {
          bVar2 = p[1] == '\t';
        }
        if (!bVar2) break;
        p = p + 1;
      }
      if ((p != end) &&
         ((pcVar1 = p + 1, *p == '\n' || ((*p == '\r' && (pcVar1 = p + 2, p[1] == '\n')))))) {
        p = pcVar1;
        *length = number;
        return p;
      }
    }
  }
  return (char *)0x0;
}