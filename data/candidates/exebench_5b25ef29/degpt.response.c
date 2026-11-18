void find_next_cell(int *ijkn,int *current_ijk,int *face_sect,double *vv,int *next_ijk)

{
  int iVar1;
  int face1_sect [3];
  int flag;
  int m;
  int j;
  int *next_ijk_local;
  double *vv_local;
  int *face_sect_local;
  int *current_ijk_local;
  int *ijkn_local;
  
  for (j = 0; j < 3; j = j + 1) {
    face1_sect[j] = face_sect[j];
  }
  for (j = 0; j < 3; j = j + 1) {
    next_ijk[j] = current_ijk[j];
  }
  for (m = 0; m < 3; m = m + 1) {
    if (face_sect[m] != -1) {
      if (face_sect[m] == 0) {
        if (*vv <= 0.0 && *vv != 0.0) {
          *next_ijk = *current_ijk + -1;
          face1_sect[m] = 1;
          iVar1 = *next_ijk;
joined_r0x001019af:
          if (iVar1 < 0) break;
        }
      }
      else if (face_sect[m] == 1) {
        if (0.0 < *vv) {
          *next_ijk = *current_ijk + 1;
          face1_sect[m] = 0;
          if (*ijkn + -1 < *next_ijk) break;
        }
      }
      else if (face_sect[m] == 2) {
        if (vv[1] <= 0.0 && vv[1] != 0.0) {
          next_ijk[1] = current_ijk[1] + -1;
          face1_sect[m] = 3;
          iVar1 = next_ijk[1];
          goto joined_r0x001019af;
        }
      }
      else if (face_sect[m] == 3) {
        if (0.0 < vv[1]) {
          next_ijk[1] = current_ijk[1] + 1;
          face1_sect[m] = 2;
          if (ijkn[1] + -1 < next_ijk[1]) break;
        }
      }
      else if (face_sect[m] == 4) {
        if (vv[2] <= 0.0 && vv[2] != 0.0) {
          next_ijk[2] = current_ijk[2] + -1;
          face1_sect[m] = 5;
          iVar1 = next_ijk[2];
          goto joined_r0x001019af;
        }
      }
      else if ((face_sect[m] == 5) && (0.0 < vv[2])) {
        next_ijk[2] = current_ijk[2] + 1;
        face1_sect[m] = 4;
        if (ijkn[2] + -1 < next_ijk[2]) break;
      }
    }
  }
  for (m = 0; m < 3; m = m + 1) {
    face_sect[m] = face1_sect[m];
  }
  return;
}