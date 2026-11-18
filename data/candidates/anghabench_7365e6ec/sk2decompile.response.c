static int llc_shdlc_w_used(int w_free, int w_used) {
  if (w_used <= w_free)
    return w_free - w_used;
  else
    return 8 + w_free - w_used;
}