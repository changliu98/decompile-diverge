void grid_point_to_grid_double(int *coord, int index, int *mesh, int *shift)
{
  int ic, ix[3];

  ix[2] = index / (mesh[0] * mesh[1]);
  ix[1] = (index - ix[2] * mesh[0] * mesh[1]) / mesh[0];
  ix[0] = index % mesh[0];

  for (ic = 0; ic < 4; ic++) {
    if (ic < 3) {
      coord[ic] = ix[ic] * 2 + shift[ic];
    }
  }

}