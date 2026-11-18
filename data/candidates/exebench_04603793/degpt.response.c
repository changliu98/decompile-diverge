void itoa(unsigned_long i,char *b)

{
  undefined1 auVar1 [16];
  char *p;
  unsigned_long shifter;
  char *b_local;
  unsigned_long i_local;
  
  p = b;
  shifter = i;
  do {
    p = p + 1;
    shifter = shifter / 10;
  } while (shifter != 0);
  *p = '\0';
  i_local = i;
  do {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = i_local;
    p[-1] = SUB161(auVar1 % ZEXT816(10),0) + '0';
    i_local = i_local / 10;
    p = p + -1;
  } while (i_local != 0);
  return;
}