void get_neighbors(int *grid, int width, int index, int *neighbors) {
  int x = index % width;
  int y = (index - x) / width;
  int y_up = y - 1;
  if (y_up < 0) y_up = width + y_up;
  int x_left = x - 1;
  if (x_left < 0) x_left = width + x_left;
  neighbors[0] = y_up * width + x;
  neighbors[1] = (y + 1) % width * width + x;
  neighbors[2] = y * width + x_left;
  neighbors[3] = y * width + (x + 1) % width;
}