void get_vector_modulo(int *a, int *b)
{
 int i = 0;
 while(1)
 {
  if(i >= 4) break;
  a[i] = a[i] % b[i];
  if(a[i] < 0) b[i] += a[i];
  else i++;
 }
}