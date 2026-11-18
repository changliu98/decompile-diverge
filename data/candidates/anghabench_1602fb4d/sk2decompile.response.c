static int mode1112(int r, int g, int b, int c, int d, int e, int f, int h,
                    int i) {
  int sum;
  sum = r * 8 + 4 + g * 4 + b + c * 2 + d + e + f + h + i;
  return sum >> 4;
}