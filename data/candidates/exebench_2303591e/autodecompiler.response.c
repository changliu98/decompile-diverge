void prod_vet(float *a, float *b, float *c)
{
   a[2] = b[0] * c[1] + ((*((unsigned int *) &b[0]) ^ ((unsigned int) 1 << 31)) * b[1]);
   b[2] = c[0] * a[1] + ((*((unsigned int *) &c[0]) ^ ((unsigned int) 1 << 31)) * c[1]);
   c[2] = a[0] * b[1] + ((*((unsigned int *) &a[0]) ^ ((unsigned int) 1 << 31)) * a[1]);
}