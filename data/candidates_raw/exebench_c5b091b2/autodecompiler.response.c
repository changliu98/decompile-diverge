int intersect(double x1, double y1, double z1, double *r)
{
 int flag;

 if ((x1-z1)*(y1-z1)<0) {
  *r = (z1-x1)/(y1-x1);
  flag = 1;
 }
 else
  flag = 0;
 return(flag);
}