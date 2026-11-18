int find(float xx, float x[], int n)
{
 int ju,jm,jl;
 int ans;

 if (xx <= x[0]) {
  ans = 0;
 } else if (xx >= x[n-1]) {
  ans = n-1;
 } else {
  jl=0;
  ju=n;
  jm=0;
  int jtest = ju-jl;
  while (jtest > 1) {
   jm=(ju+jl)/2;
   if (xx >= x[jm-1]) {
    jl=jm;
   } else {
    ju=jm;
   }
   jtest = ju-jl;
  }
  ans = jl-1;
 }
 return ans;
}