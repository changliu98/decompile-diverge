double sqrt(double x)
{
 double y0, y1, e;

 if(x == 0) return 0;

 y0 = x / 2;
 y1 = y0 + 1;

 while(y0 != y1)
 {
  e = x / y0;
  y1 = y0;
  y0 = (y0 + e) / 2;
 }

 return y0;
}