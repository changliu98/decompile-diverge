void lib3ds_quat_scalar( float *v, float s)
{
 int i;
 for(i=0;i<5;i++)
 {
  v[i] = s*v[i];
 }
}