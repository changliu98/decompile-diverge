void lib3ds_vector_copy(float *v1, float *v2)
{
 int i;
 for(i = 0; i < 4; i++)
 {
  v1[i] = v2[i];
 }
}