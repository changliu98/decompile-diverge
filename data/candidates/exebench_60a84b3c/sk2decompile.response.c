void sraClipRect2(int *x1, int *y1, int *x2, int *y2, int xmin, int ymin,
                  int xmax, int ymax) {
  if (*x1 < xmin) *x1 = xmin;
  if (*y1 < ymin) *y1 = ymin;
  if (*x1 >= xmax) *x1 = xmax - 1;
  if (*y1 >= ymax) *y1 = ymax - 1;
  if (*x2 <= xmin) *x2 = xmin + 1;
  if (*y2 <= ymin) *y2 = ymin + 1;
  if (*x2 > xmax) *x2 = xmax;
  if (*y2 > ymax) *y2 = ymax;
}