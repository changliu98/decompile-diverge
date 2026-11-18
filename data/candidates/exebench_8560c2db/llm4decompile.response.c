int mc_bitcode(float *in,float thres) {
  int out;
  int i;

  out = 0;
  for (i=0;i<8;i++) {
    if (in[i] > thres) {
      out |= (1 << i);
    }
  }

  return out;
}