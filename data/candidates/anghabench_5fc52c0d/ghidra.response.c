void sjis2jis(uchar *p1,uchar *p2)

{
  byte bVar1;
  char cVar2;
  undefined1 local_2c;
  int cell;
  int row;
  int shift;
  uchar c2;
  uchar c1;
  uchar *p2_local;
  uchar *p1_local;
  
  bVar1 = *p2;
  cVar2 = -0x50;
  if (*p1 < 0xa0) {
    cVar2 = 'p';
  }
  if (bVar1 < 0x9f) {
    local_2c = (0x7f < bVar1) + '\x1f';
  }
  else {
    local_2c = '~';
  }
  *p1 = (*p1 - cVar2) * '\x02' - (bVar1 < 0x9f);
  *p2 = *p2 - local_2c;
  return;
}