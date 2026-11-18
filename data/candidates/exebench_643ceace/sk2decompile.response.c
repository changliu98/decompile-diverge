void image_fit(int width, int height, int max_width, int max_height,
               int *new_width, int *new_height, char fit) {
  float ratio = (float)height / (float)width;
  if (fit < 1 || fit > 2) {
    fit = (float)max_height / (float)max_width > ratio ? 1 : 2;
  }
  if (fit == 1) {
    *new_height = (int)(ratio * max_width);
    *new_width = max_width;
  } else {
    *new_width = (int)(max_height / ratio);
    *new_height = max_height;
  }
}