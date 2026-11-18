void get_vector_modulo(int *v, int *m)
{
 int i;

 for (i = 0; i < 3; i++) {
  v[i] %= m[i];
  if (v[i] < 0)
   v[i] += m[i];
 }
}