bool __cdecl sraClipRect2(int *x, int *y, int *x2, int *y2, int cx_0, int cy, int cx2, int cy2)
{
  // Clamp the top-left corner to be within the bounding box [cx_0, cy, cx2, cy2]
  if (*x < cx_0)
    *x = cx_0;
  if (*y < cy)
    *y = cy;
  if (*x >= cx2)
    *x = cx2 - 1;
  if (*y >= cy2)
    *y = cy2 - 1;

  // Clamp the bottom-right corner to be within the bounding box
  if (*x2 <= cx_0)
    *x2 = cx_0 + 1;
  if (*y2 <= cy)
    *y2 = cy + 1;
  if (*x2 > cx2)
    *x2 = cx2;
  if (*y2 > cy2)
    *y2 = cy2;

  // Return true if the resulting rectangle has a valid area (width > 0 and height > 0)
  return (*x2 > *x) && (*y2 > *y);
}