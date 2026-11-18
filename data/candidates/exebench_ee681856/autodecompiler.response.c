void c_saxpy(int n, double da, double dx[], double dy[])
{
 int i,m;

 if(n <= 0 || da == 0.0e0) return;
 m = n % 4;
 if(m != 0)
 {
  for(i = 1; i <= m; i++) dy[i-1] = dy[i-1] + da*dx[i-1];
  if(n < 4) return;
 }
 for(i = m+1; i <= n; i += 4)
 {
  dy[i-1] = dy[i-1] + da*dx[i-1];
  dy[i+1 -1] = dy[i+1 -1] + da*dx[i+1 -1];
  dy[i+2 -1] = dy[i+2 -1] + da*dx[i+2 -1];
  dy[i+3 -1] = dy[i+3 -1] + da*dx[i+3 -1];
 }
}