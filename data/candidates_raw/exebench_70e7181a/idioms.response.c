void get_y_edges(int x1, int y1, int x2, int y2, int *uy1, int *uy2, int *ly1, int *ly2, int num_pixels)
{
  int w = x2 - x1 + 1;
  if (w > 0) {
    *uy1 = y1;
    *uy2 = y1 + num_pixels / w - 1;
    *ly1 = y1 + num_pixels / w;
    *ly2 = y2;
  }
}