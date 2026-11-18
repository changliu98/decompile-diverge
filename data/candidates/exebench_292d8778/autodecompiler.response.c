void lib3ds_quat_copy(float *a, float *b)
{
 int i;
 for(i=0;i<5;i++)
 {
  a[i] = b[i];
 }
}