double log2(double x)
{
 double y=1, e=10;
 while(1) {
  if(x>e) {y++; e*=10;}
  else return y;
 }
}