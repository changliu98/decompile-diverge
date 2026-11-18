// Advances the indices (i, j) to the next position in a p-ary coordinate system.
// Increments j; if j reaches p, it resets to 0 and increments i.
void next(int *row, int *col, int base)
{
  // Increment the second index
  *col = *col + 1;
  // If the second index reaches the limit p, reset it to 0 and increment the first index
  if (*col == base) {
    *col = 0;
    *row = *row + 1;
  }
}