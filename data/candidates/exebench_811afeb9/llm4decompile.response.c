int bbox(int nV, double *vertex, double *dv)
{
  int i,j,k,t;
  double bmin[3], bmax[3];

  for (j=0; j<3; j++)
    bmin[j]=bmax[j]=vertex[j];

  for (i=1; i<nV; i++)
    for (j=0; j<3; j++) {
      if (vertex[3*i+j]<bmin[j]) bmin[j]=vertex[3*i+j];
      if (vertex[3*i+j]>bmax[j]) bmax[j]=vertex[3*i+j];
    }

  for (t=0; t<3; t++)
    dv[t]=(bmin[t]+bmax[t])/2.0;

  for (t=0; t<3; t++) {
    dv[t+3]=1.0;
    while (dv[t+3]*(bmax[t]-bmin[t])<1.0) dv[t+3]*=10.0;
    while (dv[t+3]*(bmax[t]-bmin[t])>1.0) dv[t+3]/=10.0;
  }

  for (i=0; i<3; i++)
    for (j=i+1; j<3; j++)
      if (dv[i]<dv[j]) {
        t=dv[i]; dv[i]=dv[j]; dv[j]=t;
      }

  if (dv[3]<dv[4]) dv[3]/=10.0;
  if (dv[4]<dv[5]) dv[4]/=10.0;
  if (dv[3]<dv[4]) dv[3]/=10.0;
  if (dv[4]<dv[5]) dv[4]/=10.0;
  if (dv[3]<dv[4]) dv[3]/=10.0;
  if (dv[4]<dv[5]) dv[4]/=10.0;

  return(0);
}