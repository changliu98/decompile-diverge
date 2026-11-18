void lib3ds_vector_max(float *a, float *b)
{
 int i;
 for(i=0;i<4;i++) {
  if(b[i]>a[i]) a[i]=b[i];
 }
}