void makeSinTable(void) {
  int i;
  for (i = 0; i < 256; i++) {
    sinTable[256 + i] = sinTable[256 - i - 1];
  }
  for (i = 0; i < 512; i++) {
    sinTable[512 + i] = sinTable[i] | 0x8000;
  }
  for (i = 0; i < 512; i++) {
    sinTable2[i] = sinTable[i];
  }
  for (i = 512; i < 1024; i++) {
    sinTable2[i] = 0x0fff;
  }
}