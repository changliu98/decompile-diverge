/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void makeSinTable(void)

{
  int x;
  
  for (x = 0; x < 0x100; x = x + 1) {
    fullsin_table[x + 0x100] = fullsin_table[0xff - x];
  }
  for (x = 0; x < 0x200; x = x + 1) {
    fullsin_table[x + 0x200] = fullsin_table[x] | 0x8000;
  }
  for (x = 0; x < 0x200; x = x + 1) {
    halfsin_table[x] = fullsin_table[x];
  }
  for (x = 0x200; x < 0x400; x = x + 1) {
    halfsin_table[x] = 0xfff;
  }
  return;
}