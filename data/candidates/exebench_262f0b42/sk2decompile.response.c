void breakup(short *b, unsigned short n) {
  int i;
  unsigned short m;
  m = n;
  for (i = 0; i < 13; i++) b[i] = 0;
  if (m >= 4096) {
    b[12] = 1;
    m -= 4096;
  }
  if (m >= 2048) {
    b[11] = 1;
    m -= 2048;
  }
  if (m >= 1024) {
    b[10] = 1;
    m -= 1024;
  }
  if (m >= 512) {
    b[9] = 1;
    m -= 512;
  }
  if (m >= 256) {
    b[8] = 1;
    m -= 256;
  }
  if (m >= 128) {
    b[7] = 1;
    m -= 128;
  }
  if (m >= 64) {
    b[6] = 1;
    m -= 64;
  }
  if (m >= 32) {
    b[5] = 1;
    m -= 32;
  }
  if (m >= 16) {
    b[4] = 1;
    m -= 16;
  }
  if (m >= 8) {
    b[3] = 1;
    m -= 8;
  }
  if (m >= 4) {
    b[2] = 1;
    m -= 4;
  }
  if (m >= 2) {
    b[1] = 1;
    m -= 2;
  }
  if (m == 1) b[0] = 1;
}