void pa(float e[4], float t, float t2)
      {
  long j;
  for(j=0;j<6;j++)
     {
        e[0] = (e[0]+e[1]+e[2]-e[3])*t;
        e[1] = (e[0]+e[1]-e[2]+e[3])*t;
        e[2] = (e[0]-e[1]+e[2]+e[3])*t;
        e[3] = (-e[0]+e[1]+e[2]+e[3])/t2;
     }

  return;
      }