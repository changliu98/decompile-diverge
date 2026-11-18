void convertscreenvertex(vertex3f *v,int resx,int resy)
{
  v->x=(v->x-resx/2)/(float)(resx/2);
  v->y=(resy/2-v->y)/(float)(resx/2);
  v->z=1.0;
}