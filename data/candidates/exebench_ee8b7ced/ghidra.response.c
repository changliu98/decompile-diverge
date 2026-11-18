void get_neighbors(int *lattice,int n_side,int index,int *neigh)

{
  int iVar1;
  int iVar2;
  int j;
  int i;
  int right;
  int left;
  int down;
  int up;
  int *neigh_local;
  int index_local;
  int n_side_local;
  int *lattice_local;
  
  iVar2 = index % n_side;
  iVar1 = (index - iVar2) / n_side;
  up = iVar1 + -1;
  if (up < 0) {
    up = n_side - up;
  }
  left = iVar2 + -1;
  if (left < 0) {
    left = n_side - left;
  }
  *neigh = iVar2 + n_side * up;
  neigh[1] = iVar2 + n_side * ((iVar1 + 1) % n_side);
  neigh[2] = left + n_side * iVar1;
  neigh[3] = (iVar2 + 1) % n_side + n_side * iVar1;
  return;
}