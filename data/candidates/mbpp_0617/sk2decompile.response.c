int _get_page_count(int width, int height, int size) {
  int min, max;
  if (width < height)
    min = width;
  else
    min = height;
  if (width > height)
    max = width;
  else
    max = height;
  if (size >= max) return (size + max - 1) / max;
  if (size == 0) return 0;
  if (size == min) return 1;
  return 2;
}