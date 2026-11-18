float interp_tri(float *g,float x,float y,int ig)
{
 float g1,g2,g3,g4;
 double xx,yy,x1,x2,x3,x4,y1,y2,y3,y4;
 double dx,dy;

 if(x<1.e-5) xx=0.; else xx=x;
 if(y<1.e-5) yy=0.; else yy=y;
 if(xx==0. && yy==0.) return(g[0]);
 if(xx==1. && yy==0.) return(g[1]);
 if(xx==1. && yy==1.) return(g[3]);
 if(xx==0. && yy==1.) return(g[2]);

 if(ig>0) {
  x1=g[0]; y1=g[1];
  x2=g[3]; y2=g[2];
 } else {
  xx=1.-xx;
  x1=g[1]; y1=g[0];
  x2=g[2]; y2=g[3];
 }

 if(yy<=xx) {
  x3=x1; y3=y1;
  x4=x2; y4=y2;
 } else {
  x3=x2; y3=y2;
  x4=x1; y4=y1;
  xx=1.-xx; yy=1.-yy;
 }
 g1=x3+(y3-x3)*xx;
 g2=x4+(y4-x4)*xx;
 return(g1+(g2-g1)*(yy/xx));
}