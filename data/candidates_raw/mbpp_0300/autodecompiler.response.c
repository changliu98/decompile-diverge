double bessi0(double x)
{
 double sum=1.0;
 double powx=1.0;
 int k;

 for(k=1;;k++)
 {
  double bessk=bessk0(k,x);
  powx*=x*x/4.0;
  double addit=powx/bessk;
  sum+=addit;
  if(addit<1e-7) break;
 }
 return sum;
}