float pluck(float amp, float *buf) {
  int i;
  float out, tmp;
  buf[0] += 1.0;
  if (buf[1] <= buf[0]) {
    i = 4;
    buf[0] = 4.0;
  } else {
    i = (int)buf[0];
  }
  out = buf[i];
  tmp = amp + buf[2] * out;
  buf[i] = tmp + buf[3] * buf[i - 1];
  return out;
}