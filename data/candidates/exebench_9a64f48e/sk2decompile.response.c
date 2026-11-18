int vis5d_color_table_set_alpha(float alpha, float color[]) {
  color[3] = alpha;
  if (alpha < 0) {
    color[5] = 0;
    color[6] = 255;
    if (alpha == -2) {
      color[2] = 0;
      color[3] = -1;
    } else {
      color[2] = 2;
    }
  } else {
    color[5] = alpha;
    color[6] = alpha;
    color[3] = alpha;
  }
  return 0;
}