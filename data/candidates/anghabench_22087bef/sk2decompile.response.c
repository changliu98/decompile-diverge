unsigned char linear2ulaw(short pcm_val) {
  int mask;
  int seg;
  int uval;
  short t_val;
  t_val = pcm_val;
  mask = (t_val >> 8) & 0x80;
  if (mask != 0) t_val = -t_val;
  t_val = t_val + BIAS;
  seg = seg_u[(t_val >> 7) & 0xFF];
  uval = mask | (seg << 4) | ((t_val >> (seg + 3)) & 0xF);
  return ~uval;
}