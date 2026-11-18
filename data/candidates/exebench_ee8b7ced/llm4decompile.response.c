void get_neighbors(int *lattice, int n_side, int index, int *neigh) {







  int i, j;
  int up, down, left, right;

  i = index % n_side;
  j = (index - i) / n_side;

  up = j - 1;
  if (up < 0) up = n_side + up;
  down = (j + 1) % n_side;
  left = i - 1;
  if (left < 0) left = n_side + left;
  right = (i + 1) % n_side;

  neigh[0] = up * n_side + i;
  neigh[1] = down * n_side + i;
  neigh[2] = j * n_side + left;
  neigh[3] = j * n_side + right;

}