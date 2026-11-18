void __cdecl get_neighbors(int *lattice, int n_side, int index, int *neigh)
{
  int j; // [rsp+0h] [rbp-30h]
  int i; // [rsp+4h] [rbp-2Ch]
  int left; // [rsp+Ch] [rbp-24h]
  int up; // [rsp+14h] [rbp-1Ch]

  j = index % n_side;
  i = (index - index % n_side) / n_side;
  up = i - 1;
  if ( i - 1 < 0 )
    up = n_side - up;
  left = j - 1;
  if ( j - 1 < 0 )
    left = n_side - left;
  *neigh = up * n_side + j;
  neigh[1] = (i + 1) % n_side * n_side + j;
  neigh[2] = i * n_side + left;
  neigh[3] = i * n_side + (j + 1) % n_side;
}