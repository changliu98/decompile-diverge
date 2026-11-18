double _calc_area(int side, int height) {
  double area;
  if (side < 0 || height < 0) return -1;
  area = 3.0 * sqrt(3.0);
  area *= pow((double)side, 2.0);
  area /= (double)(4 * height);
  return area;
}