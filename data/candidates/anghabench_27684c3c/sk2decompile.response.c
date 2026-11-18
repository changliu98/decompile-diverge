int resize_height(double ratio, double height, double width) {
  double new_height;
  int new_width;
  new_height = height / ratio;
  new_width = (int)(width * new_height + 0.5);
  return new_width;
}