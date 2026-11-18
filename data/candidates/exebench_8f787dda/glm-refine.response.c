void __cdecl index_to_xwy(int index, int width, int *x, int *y)
{
  // The x coordinate is the remainder of the index divided by the width (column index)
  *x = index % width;
  
  // The y coordinate is the quotient of the index divided by the width (row index)
  *y = index / width;
}