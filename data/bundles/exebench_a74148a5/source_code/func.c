
float getUniform(int a, int c, int m, float* x)
{
 float num = a*(*x) + c;
 int num_mod = num / m;
 num = num - num_mod*m;

 *x = num / m;
 return *x;
}
