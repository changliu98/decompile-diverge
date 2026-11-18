#include <stdio.h>

#include <stdlib.h>

#include <math.h>

void get_neighbors(int *lattice, int n_side, int index, int *neigh){
  int up, down, left, right;
  int i;
  int j;

  j = index%n_side;
  i = (index-j)/n_side;

  up = (i-1);if(up<0)up=n_side-up;
  left = (j-1);if(left<0)left=n_side-left;
  down = (i+1)%n_side;
  right = (j+1)%n_side;


  neigh[0] = j + (n_side * up);
  neigh[1] = j + (n_side * down);
  neigh[2] = left + (n_side * i);
  neigh[3] = right + (n_side * i);
}
