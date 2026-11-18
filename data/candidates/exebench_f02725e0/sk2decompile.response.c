void foo(unsigned short *p) {
  unsigned short x = 0xffff;
  *p = x;
  if (*p != x)
    ;
}