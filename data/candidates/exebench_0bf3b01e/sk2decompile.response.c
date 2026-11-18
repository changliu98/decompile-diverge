void DoAdjust(int *x, int *y, int dx, int dy, int w, int h) {
  --(*x);
  --(*y);
  (*x) += dx;
  if ((*x) < 0) {
    (*x) = w - (*x);
    (*y) -= (*x) / w;
    (*x) = w - (*x) % w;
  }
  (*y) += (*x) / w;
  (*x) %= w;
  (*y) += dy;
  ++(*x);
  ++(*y);
}