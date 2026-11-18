int do_map(char *b,int map,char c)

{
  bool bVar1;
  int n;
  char c_local;
  int map_local;
  char *b_local;
  
  if (c == '\b') {
    if ((map & 0x80U) == 0) {
      *b = '\b';
    }
    else {
      *b = '\x7f';
    }
    n = 1;
  }
  else if (c == '\n') {
    if ((map & 8U) == 0) {
      if ((map & 0x10U) == 0) {
        bVar1 = (map & 0x20U) == 0;
        if (bVar1) {
          *b = '\n';
        }
        n = (int)bVar1;
      }
      else {
        *b = '\r';
        b[1] = '\n';
        n = 2;
      }
    }
    else {
      *b = '\r';
      n = 1;
    }
  }
  else if (c == '\r') {
    if ((map & 1U) == 0) {
      if ((map & 2U) == 0) {
        bVar1 = (map & 4U) == 0;
        if (bVar1) {
          *b = '\r';
        }
        n = (int)bVar1;
      }
      else {
        *b = '\r';
        b[1] = '\n';
        n = 2;
      }
    }
    else {
      *b = '\n';
      n = 1;
    }
  }
  else if (c == '\x7f') {
    if ((map & 0x40U) == 0) {
      *b = '\x7f';
    }
    else {
      *b = '\b';
    }
    n = 1;
  }
  else {
    *b = c;
    n = 1;
  }
  return n;
}