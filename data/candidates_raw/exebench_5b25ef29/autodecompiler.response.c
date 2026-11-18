void face_change(int *nijk, int *ijk, int *facemod, double *vxyz,
                 int *newijk)
{
  int i, j, flag=1;
  int face1_sect[4];

  for(j=0;j<4;j++) face1_sect[j] = facemod[j];
  for(j=0;j<4;j++) newijk[j] = ijk[j];

  for(i=0;i<4;i++)
    {
      if(facemod[i] == -1) continue;

      if(facemod[i] == 0)
        {
          if(vxyz[0] < 0.0)
            {
              newijk[0] = ijk[0] - 1;
              face1_sect[i] = 1;
              if(newijk[0] < 0) break;
            }
        }
      else if(facemod[i] == 1)
        {
          if(vxyz[0] > 0.0)
            {
              newijk[0] = ijk[0] + 1;
              face1_sect[i] = 0;
              if(newijk[0] > nijk[0]-1) break;
            }
        }
      else if(facemod[i] == 2)
        {
          if(vxyz[1] < 0.0)
            {
              newijk[1] = ijk[1] - 1;
              face1_sect[i] = 3;
              if(newijk[1] < 0) break;
            }
        }
      else if(facemod[i] == 3)
        {
          if(vxyz[1] > 0.0)
            {
              newijk[1] = ijk[1] + 1;
              face1_sect[i] = 2;
              if(newijk[1] > nijk[1]-1) break;
            }
        }
      else if(facemod[i] == 4)
        {
          if(vxyz[2] < 0.0)
            {
              newijk[2] = ijk[2] - 1;
              face1_sect[i] = 5;
              if(newijk[2] < 0) break;
            }
        }
      else if(facemod[i] == 5)
        {
          if(vxyz[2] > 0.0)
            {
              newijk[2] = ijk[2] + 1;
              face1_sect[i] = 4;
              if(newijk[2] > nijk[2]-1) break;
            }
        }
    }

  for(i=0;i<4;i++) facemod[i] = face1_sect[i];
}