void calculate_proportions(int width, int height, int *new_width,
                           int *new_height) {
  int w = new_width ? *new_width : 0;
  int h = new_height ? *new_height : 0;
  if (width > 0 && width >= height && w > 0 && h <= 0)
    h = w * height / width;
  else if (height > 0)
    w = h * width / height;
  if (new_width) *new_width = w;
  if (new_height) *new_height = h;
}