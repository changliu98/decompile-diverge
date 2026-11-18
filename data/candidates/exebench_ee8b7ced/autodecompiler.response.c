void get_neighbors(int *lat, int n_side, int index, int *neigh)
{
  int ix, iy;
  int up, down, left, right;

  ix = index%n_side;
  iy = (index-ix)/n_side;

  up = iy-1;
  if(up<0) up = n_side-up;
  down = (iy+1)%n_side;
  left = ix-1;
  if(left<0) left = n_side-left;
  right = (ix+1)%n_side;

  neigh[0] = ix + up*n_side;
  neigh[1] = ix + down*n_side;
  neigh[2] = left + iy*n_side;
  neigh[3] = right + iy*n_side;
}