void f1(int n, float da, float dx[], float dy[])
{
 int i;

 for (i=0; i<n; i++)
  dy[i] += da*dx[i];
}