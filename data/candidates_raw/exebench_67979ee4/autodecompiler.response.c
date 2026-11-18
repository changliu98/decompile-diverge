void glmMultQuaternionf(float x1, float y1, float z1, float w1,
                        float x2, float y2, float z2, float w2,
                        float *x, float *y, float *z, float *w)
{
  *x = -(*(unsigned int*)(&x1) ^ (1<<31))*x2 + w1*x2 + z1*z2 + -(*(unsigned int*)(&y1) ^ (1<<31))*y2;
  *y = w1*y2 + y1*x2 + -(*(unsigned int*)(&z1) ^ (1<<31))*z2 + -(*(unsigned int*)(&w1) ^ (1<<31))*y2;
  *z = z1*x2 + -(*(unsigned int*)(&y1) ^ (1<<31))*y2 + w1*z2 + x1*w2;
  *w = w1*w2 + x1*x2 + y1*y2 + z1*z2;
}