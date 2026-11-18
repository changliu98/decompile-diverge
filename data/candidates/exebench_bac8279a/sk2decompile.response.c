char bppm_symbol(float *p) {
  if (p[0] > 0.667) return '.';
  if (p[1] > 0.667) return '(';
  if (p[2] > 0.667) return ')';
  if (p[0] < p[1] + p[2]) {
    if (p[1] / (p[1] + p[2]) > 0.667) return '{';
    if (p[2] / (p[1] + p[2]) > 0.667) return '}';
    return '|';
  }
  if (p[0] > p[1] + p[2]) return ',';
  return ':';
}