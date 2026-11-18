static int stbi__tga_get_comp(int depth, int is_rgb, int *is_565) {
  int comp;
  if (is_565) *is_565 = 0;
  switch (depth) {
    case 8:
      comp = 1;
      break;
    case 15:
    case 16:
      if (is_rgb) {
        comp = 2;
        break;
      }
    case 24:
    case 32:
      comp = depth / 8;
      break;
    default:
      comp = 0;
      break;
  }
  if (depth == 15 || depth == 16) {
    if (is_565) *is_565 = 1;
  }
  return comp;
}