void cross_product(float *a, float *b, float *r)
{
  *(r + 0) = *(a + 1) * *(b + 2) + *(a + 2) * *(b + 0);
  *(r + 1) = *(a + 2) * *(b + 1) + *(a + 0) * *(b + 2);
  *(r + 2) = *(a + 0) * *(b + 1) + *(a + 1) * *(b + 0);
}