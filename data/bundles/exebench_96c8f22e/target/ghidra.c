void pa(float *e,float t,float t2)

{
  long j;
  float t2_local;
  float t_local;
  float *e_local;
  
  for (j = 0; j < 6; j = j + 1) {
    *e = ((*e + e[1] + e[2]) - e[3]) * t;
    e[1] = (((*e + e[1]) - e[2]) + e[3]) * t;
    e[2] = ((*e - e[1]) + e[2] + e[3]) * t;
    e[3] = (-*e + e[1] + e[2] + e[3]) / t2;
  }
  return;
}