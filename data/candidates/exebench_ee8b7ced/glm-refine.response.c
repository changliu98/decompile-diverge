void __cdecl get_neighbors(int *lattice, int n_side, int index, int *neigh)
{
  // 'lattice' is unused in this function, but kept for signature compatibility.
  
  // Calculate 2D coordinates (i, j) from the 1D index
  int j = index % n_side;
  int i = index / n_side; // Compiler optimization: (index - index % n_side) / n_side is equivalent to index / n_side

  // Calculate wrapped 'up' coordinate (handles top-edge wrap-around)
  int up = i - 1;
  if (up < 0)
    up = n_side - up; // Note: Evaluates to n_side - (-1) = n_side + 1. This is semantically identical to the original.

  // Calculate wrapped 'left' coordinate (handles left-edge wrap-around)
  int left = j - 1;
  if (left < 0)
    left = n_side - left; // Evaluates to n_side + 1

  // Map the 4 neighbors back to 1D indices and store them in the output array
  neigh[0] = up * n_side + j;
  neigh[1] = ((i + 1) % n_side) * n_side + j;
  neigh[2] = i * n_side + left;
  neigh[3] = i * n_side + ((j + 1) % n_side);
}