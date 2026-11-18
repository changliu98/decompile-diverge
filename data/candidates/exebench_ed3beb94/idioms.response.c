void math_matrix_copy(float a[16], float b[16])
{
 int i;
 for (i = 0; i < 16; i++)
  b[i] = a[i];
}