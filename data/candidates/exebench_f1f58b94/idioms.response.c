void sort4_sorting_network_simple_swap(short *p)
{
  short a; short b; short c; short d;
  if (p[0]<p[1]) a=p[0],b=p[1];
  else a=p[1],b=p[0];
  if (p[2]<p[3]) c=p[2],d=p[3];
  else c=p[3],d=p[2];
  if (a<c) p[0]=a,p[1]=c,p[2]=b,p[3]=d;
  else p[0]=c,p[1]=a,p[2]=d,p[3]=b;
  if (p[1]<p[2]) a=p[1],b=p[2];
  else a=p[2],b=p[1];
  if (a<p[3]) p[1]=a,p[2]=p[3],p[3]=b;
  else p[1]=p[3],p[2]=a,p[3]=b;
  if (p[1]<p[0]) a=p[1],b=p[0];
  else a=p[0],b=p[1];
  if (a<p[2]) p[1]=a,p[0]=p[2],p[2]=b;
  else p[1]=p[2],p[0]=a,p[2]=b;
}