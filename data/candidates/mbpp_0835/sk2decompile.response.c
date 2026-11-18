float _calc_ratio(int x1, int y1, int x2, int y2) {
  float ratio;
  ratio = (float)(y2 - y1) / (float)(x2 - x1);
  return ratio;
}