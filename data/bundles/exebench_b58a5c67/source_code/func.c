
void r2d(double *ra,double *dec,int *ih,double *am,
           char *isgn,int *id,double *amin)
{
char iminus = '-';
char iplus = '+';
float rad= 0.0174532925199;
float deg,hours;
int ira;




hours = *ra / rad/ 15.0;

while (hours > 24.) hours = hours -24.;
ira = (int)hours;
*ih = ira;
*am = (hours - (float)ira) * 60.;
*am = *am+1.e-6;
if(*am >= 60.) {
      *am = *am-60.;
      *ih = *ih+1;
}
if (*ih >= 24)
    *ih= *ih-24;



if (*dec < 0) {
   *isgn = iminus;
   *dec = - *dec;
}
else
   *isgn = iplus;
deg = *dec/rad;
*id=(int)deg;
*amin=(deg-(float)*id) * 60.;
return;
}
