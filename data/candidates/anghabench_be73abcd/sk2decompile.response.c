int val_seg(int seg) {
  int val = 0;
  int seg_val = seg >> 7;
  if (seg_val & 0xf0) {
    seg_val >>= 4;
    val += 4;
  }
  if (seg_val & 0xc) {
    seg_val >>= 2;
    val += 2;
  }
  if (seg_val & 0x2) val++;
  return val;
}