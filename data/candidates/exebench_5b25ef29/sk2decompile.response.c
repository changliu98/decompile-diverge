void find_next_cell(int *dims, int *icell, int *dir, double *d, int *nextcell) {
  int i, j, newdir[3];
  int found = 1;
  for (i = 0; i < 3; i++) newdir[i] = dir[i];
  for (i = 0; i < 3; i++) nextcell[i] = icell[i];
  for (j = 0; j < 3; j++) {
    if (dir[j] == -1) continue;
    if (dir[j] == 0) {
      if (d[0] < 0.0) {
        nextcell[0] = icell[0] - 1;
        newdir[j] = 1;
        if (nextcell[0] < 0) {
          found = 0;
          break;
        }
      }
    } else if (dir[j] == 1) {
      if (d[0] > 0.0) {
        nextcell[0] = icell[0] + 1;
        newdir[j] = 0;
        if (nextcell[0] > dims[0] - 1) {
          found = 0;
          break;
        }
      }
    } else if (dir[j] == 2) {
      if (d[1] < 0.0) {
        nextcell[1] = icell[1] - 1;
        newdir[j] = 3;
        if (nextcell[1] < 0) {
          found = 0;
          break;
        }
      }
    } else if (dir[j] == 3) {
      if (d[1] > 0.0) {
        nextcell[1] = icell[1] + 1;
        newdir[j] = 2;
        if (nextcell[1] > dims[1] - 1) {
          found = 0;
          break;
        }
      }
    } else if (dir[j] == 4) {
      if (d[2] < 0.0) {
        nextcell[2] = icell[2] - 1;
        newdir[j] = 5;
        if (nextcell[2] < 0) {
          found = 0;
          break;
        }
      }
    } else if (dir[j] == 5) {
      if (d[2] > 0.0) {
        nextcell[2] = icell[2] + 1;
        newdir[j] = 4;
        if (nextcell[2] > dims[2] - 1) {
          found = 0;
          break;
        }
      }
    }
  }
  for (j = 0; j < 3; j++) dir[j] = newdir[j];
}