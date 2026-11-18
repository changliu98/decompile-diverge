void get_neighbors(int *lattice, int n_side, int index, int *neigh)
{
  int i; int j; int up; int left;
  i = index / n_side;
  j = index % n_side;
  up = i - 1;
  if (up < 0) up = n_side - up;
  left = j - 1;
  if (left < 0) left = n_side - left;
  neigh[0] = up * n_side + j;
  neigh[1] = (i + 1) % n_side * n_side + j;
  neigh[2] = i * n_side + left;
  neigh[3] = i * n_side + (j + 1) % n_side;
  return;
}