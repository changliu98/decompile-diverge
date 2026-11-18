void nsvg__addPath(NSVGparser *p,char closed)

{
  NSVGattrib *pNVar1;
  NSVGpath *__s;
  float *pfVar2;
  float fVar3;
  int i;
  float *curve;
  float bounds [4];
  NSVGpath *path;
  NSVGattrib *attr;
  char closed_local;
  NSVGparser *p_local;
  
  pNVar1 = nsvg__getAttr(p);
  if (3 < p->npts) {
    if (closed != '\0') {
      nsvg__lineTo(p,*p->pts,p->pts[1]);
    }
    if (p->npts % 3 == 1) {
      __s = malloc(0x28);
      if (__s != (NSVGpath *)0x0) {
        memset(__s,0,0x28);
        pfVar2 = malloc((long)(p->npts << 1) << 2);
        __s->pts = pfVar2;
        if (__s->pts != (float *)0x0) {
          __s->closed = closed;
          __s->npts = p->npts;
          for (i = 0; i < p->npts; i = i + 1) {
            nsvg__xformPoint(__s->pts + (i << 1),__s->pts + (i * 2 + 1),p->pts[i << 1],
                             p->pts[i * 2 + 1],pNVar1->xform);
          }
          for (i = 0; i < __s->npts + -1; i = i + 3) {
            nsvg__curveBounds(bounds,__s->pts + (i << 1));
            if (i == 0) {
              __s->bounds[0] = bounds[0];
              __s->bounds[1] = bounds[1];
              __s->bounds[2] = bounds[2];
              __s->bounds[3] = bounds[3];
            }
            else {
              fVar3 = nsvg__minf(__s->bounds[0],bounds[0]);
              __s->bounds[0] = fVar3;
              fVar3 = nsvg__minf(__s->bounds[1],bounds[1]);
              __s->bounds[1] = fVar3;
              fVar3 = nsvg__maxf(__s->bounds[2],bounds[2]);
              __s->bounds[2] = fVar3;
              fVar3 = nsvg__maxf(__s->bounds[3],bounds[3]);
              __s->bounds[3] = fVar3;
            }
          }
          __s->next = p->plist;
          p->plist = __s;
          return;
        }
      }
      if (__s != (NSVGpath *)0x0) {
        if (__s->pts != (float *)0x0) {
          free(__s->pts);
        }
        free(__s);
      }
    }
  }
  return;
}