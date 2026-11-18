int pow2(int k,int p)
{
 int i,t=1;
 for(i=0;;i++)
 {
  if(i>=k)
   return t;
  t=(t*2)%p;
 }
}