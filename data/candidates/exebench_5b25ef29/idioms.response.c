void find_next_cell(int *ijkn, int *current_ijk, int *face_sect, double *vv, int *next_ijk)
{
  int i; int j; int k;
  int *ijkna = ijkn;
  int *current_ijka = current_ijk;
  int *face_secta = face_sect;
  double *vva = vv;
  int *next_ijka = next_ijk;
  int flag = 1;
  int face1_sect[3];
  for (i = 0; i < 3; i++)
    face1_sect[i] = face_secta[i];
  for (i = 0; i < 3; i++)
    next_ijka[i] = current_ijka[i];
  for (j = 0; j < 3; j++)
    if (face_secta[j] != -1)
      if (face_secta[j] == 0)
        if (vva[0] < 0.)
        {
          next_ijka[0] = current_ijka[0] - 1;
          face1_sect[j] = 1;
          if (next_ijka[0] < 0)
            goto out;
        }
      else
        if (face_secta[j] == 1)
          if (vva[0] > 0.)
          {
            next_ijka[0] = current_ijka[0] + 1;
            face1_sect[j] = 0;
            if (next_ijka[0] > ijkna[0] - 1)
              goto out;
          }
        else
          if (face_secta[j] == 2)
            if (vva[1] > 0.)
            {
              next_ijka[1] = current_ijka[1] + 1;
              face1_sect[j] = 2;
              if (next_ijka[1] > ijkna[1] - 1)
                goto out;
            }
          else
            if (face_secta[j] == 3)
              if (vva[1] < 0.)
              {
                next_ijka[1] = current_ijka[1] - 1;
                face1_sect[j] = 3;
                if (next_ijka[1] < 0)
                  goto out;
              }
            else
              if (face_secta[j] == 4)
                if (vva[2] < 0.)
                {
                  next_ijka[2] = current_ijka[2] - 1;
                  face1_sect[j] = 5;
                  if (next_ijka[2] < 0)
                    goto out;
                }
              else
                if (face_secta[j] == 5)
                  if (vva[2] > 0.)
                  {
                    next_ijka[2] = current_ijka[2] + 1;
                    face1_sect[j] = 4;
                    if (next_ijka[2] > ijkna[2] - 1)
                      goto out;
                  }
out:
  for (j = 0; j < 3; j++)
    face_secta[j] = face1_sect[j];
}