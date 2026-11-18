int func0(float x, float y, float z)
{
 int i;
 int ret;

 if ((fabsf((x * x) + (y * y) + (-z * z)) < 0.0001) ||
     (fabsf((x * x) + (-y * y) + (z * z)) < 0.0001) ||
     (fabsf((-x * x) + (y * y) + (z * z)) < 0.0001))
 {
  ret = 1;
 }
 else
 {
  ret = 0;
 }

 return ret;
}