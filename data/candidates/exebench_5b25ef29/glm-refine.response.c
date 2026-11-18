void __cdecl find_next_cell(int *ijkn, int *current_ijk, int *face_sect, double *vv, int *next_ijk)
{
  int face1_sect[3];
  int m;

  // Initialize the local face array and the next_ijk array
  for (m = 0; m < 3; ++m)
  {
    face1_sect[m] = face_sect[m];
    next_ijk[m] = current_ijk[m];
  }

  for (m = 0; m < 3; ++m)
  {
    int face = face_sect[m];

    if (face == -1)
      continue;

    if (face == 0)
    {
      if (vv[0] < 0.0)
      {
        next_ijk[0] = current_ijk[0] - 1;
        face1_sect[m] = 1;
        if (next_ijk[0] < 0)
          break;
      }
    }
    else if (face == 1)
    {
      if (vv[0] > 0.0)
      {
        next_ijk[0] = current_ijk[0] + 1;
        face1_sect[m] = 0;
        if (next_ijk[0] > ijkn[0] - 1)
          break;
      }
    }
    else if (face == 2)
    {
      if (vv[1] < 0.0)
      {
        next_ijk[1] = current_ijk[1] - 1;
        face1_sect[m] = 3;
        if (next_ijk[1] < 0)
          break;
      }
    }
    else if (face == 3)
    {
      if (vv[1] > 0.0)
      {
        next_ijk[1] = current_ijk[1] + 1;
        face1_sect[m] = 2;
        if (next_ijk[1] > ijkn[1] - 1)
          break;
      }
    }
    else if (face == 4)
    {
      if (vv[2] < 0.0)
      {
        next_ijk[2] = current_ijk[2] - 1;
        face1_sect[m] = 5;
        if (next_ijk[2] < 0)
          break;
      }
    }
    else if (face == 5)
    {
      if (vv[2] > 0.0)
      {
        next_ijk[2] = current_ijk[2] + 1;
        face1_sect[m] = 4;
        if (next_ijk[2] > ijkn[2] - 1)
          break;
      }
    }
  }

  // Write back the updated face sections
  for (m = 0; m < 3; ++m)
    face_sect[m] = face1_sect[m];
}