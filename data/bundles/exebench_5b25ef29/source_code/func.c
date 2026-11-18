#include <math.h>

static void find_next_cell(int ijkn[3], int current_ijk[3], int face_sect[3],
                           double vv[3], int next_ijk[3])

{
  int j, m, flag;
  int face1_sect[3];

  flag = 1;
  for (j = 0; j < 3; j++) face1_sect[j] = face_sect[j];
  for (j = 0; j < 3; j++) next_ijk[j] = current_ijk[j];
  for (m = 0; m < 3; m++) {
    if (face_sect[m] != -1) {
      if (face_sect[m] == 0) {
        if (vv[0] < 0) {
          next_ijk[0] = current_ijk[0] - 1;
          face1_sect[m] = 1;
          if (next_ijk[0] < 0) break;
        }
      } else if (face_sect[m] == 1) {
        if (vv[0] > 0) {
          next_ijk[0] = current_ijk[0] + 1;
          face1_sect[m] = 0;
          if (next_ijk[0] > ijkn[0] - 1) break;
        }
      } else if (face_sect[m] == 2) {
        if (vv[1] < 0) {
          next_ijk[1] = current_ijk[1] - 1;
          face1_sect[m] = 3;
          if (next_ijk[1] < 0) break;
        }
      } else if (face_sect[m] == 3) {
        if (vv[1] > 0) {
          next_ijk[1] = current_ijk[1] + 1;
          face1_sect[m] = 2;
          if (next_ijk[1] > ijkn[1] - 1) break;
        }
      } else if (face_sect[m] == 4) {
        if (vv[2] < 0) {
          next_ijk[2] = current_ijk[2] - 1;
          face1_sect[m] = 5;
          if (next_ijk[2] < 0) break;
        }
      } else if (face_sect[m] == 5) {
        if (vv[2] > 0) {
          next_ijk[2] = current_ijk[2] + 1;
          face1_sect[m] = 4;
          if (next_ijk[2] > ijkn[2] - 1) break;
        }
      }
    }
  }

  for (m = 0; m < 3; m++) face_sect[m] = face1_sect[m];

  return;
}
