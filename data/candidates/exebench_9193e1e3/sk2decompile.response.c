void clip_coord(int *coord, int min, int max) {
  int c;
  c = *coord;
  c = (c < min) ? min : c;
  c = (c > max) ? max : c;
  *coord = c;
}