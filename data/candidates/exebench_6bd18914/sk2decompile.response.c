void vp8_short_inv_walsh4x4_simd(short *in, short *out) {
  int i;
  short tmp[16];
  short *ip, *op, *tp;
  short a, b, c, d;
  ip = in;
  op = out;
  tp = tmp;
  for (i = 0; i < 4; i++) {
    a = ip[0] + ip[12];
    b = ip[4] + ip[8];
    c = ip[4] - ip[8];
    d = ip[0] - ip[12];
    tp[0] = a + b;
    tp[4] = d + c;
    tp[8] = a - b;
    tp[12] = d - c;
    ip++;
    tp++;
  }
  ip = tmp;
  tp = tmp;
  for (i = 0; i < 4; i++) {
    a = ip[0] + ip[3];
    b = ip[1] + ip[2];
    c = ip[1] - ip[2];
    d = ip[0] - ip[3];
    tp[0] = (a + b + 3) >> 3;
    tp[1] = (d + c + 3) >> 3;
    tp[2] = (a - b + 3) >> 3;
    tp[3] = (d - c + 3) >> 3;
    ip += 4;
    tp += 4;
  }
  for (i = 0; i < 16; i++) {
    op[0] = tmp[i];
    op += 16;
  }
}