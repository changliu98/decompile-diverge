float vector_angle(float *v1, float *v2, int dim)
{
  float norm1=0.0;
  float norm2=0.0;
  float ip=0.0;
  float angle;
  int i;

  for (i=0; i<dim; i++) {
    ip += v1[i]*v2[i];
    norm1 += v1[i]*v1[i];
    norm2 += v2[i]*v2[i];
  }

  if (ip>0) {
    angle = ip*ip/norm2;
  }
  else {
    angle = 0.0;
  }

  return(angle);
}