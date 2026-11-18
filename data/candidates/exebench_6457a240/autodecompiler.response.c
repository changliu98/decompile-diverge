void peneira(int n, int h[])
{
 int i,j,k;
 int hv;

 k = 1;
 j = 2 * k;
 hv = h[k];
 while(j <= n)
 {
  if(j < n && h[j] < h[j+1])
   j++;
  if(hv >= h[j])
   break;
  h[k] = h[j];
  k = j;
  j = 2 * k;
 }
 h[k] = hv;
}