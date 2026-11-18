int clip(double *px,double *py,double *pz,double xmin,double xmax,double ymin,double ymax,double zmin,double zmax)

{
  int clipped;

  clipped=0;
  if(*px<xmin){*px=xmin;clipped=1;}
  else if(*px>xmax){*px=xmax;clipped=1;}
  if(*py<ymin){*py=ymin;clipped=1;}
  else if(*py>ymax){*py=ymax;clipped=1;}
  if(*pz<zmin){*pz=zmin;clipped=1;}
  else if(*pz>zmax){*pz=zmax;clipped=1;}
  return clipped;
}