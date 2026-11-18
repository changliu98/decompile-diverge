void __cdecl nsvg__addPath(NSVGparser *p, char closed)
{
  float v2; // xmm0_4
  float v3; // xmm0_4
  float v4; // xmm0_4
  float v5; // xmm0_4
  int i; // [rsp+4h] [rbp-3Ch]
  int ia; // [rsp+4h] [rbp-3Ch]
  float bounds[4]; // [rsp+10h] [rbp-30h] BYREF
  NSVGpath *path; // [rsp+20h] [rbp-20h]
  NSVGattrib *attr; // [rsp+28h] [rbp-18h]
  char closeda; // [rsp+37h] [rbp-9h]
  NSVGparser *pa; // [rsp+38h] [rbp-8h]

  pa = p;
  closeda = closed;
  attr = nsvg__getAttr(p);
  path = 0LL;
  if ( p->npts >= 4 )
  {
    if ( closeda )
      nsvg__lineTo(pa, *pa->pts, pa->pts[1]);
    if ( pa->npts % 3 == 1 )
    {
      path = (NSVGpath *)malloc(0x28uLL);
      if ( path && (memset(path, 0, sizeof(NSVGpath)), (path->pts = (float *)malloc(8LL * pa->npts)) != 0LL) )
      {
        path->closed = closeda;
        path->npts = pa->npts;
        for ( i = 0; i < pa->npts; ++i )
          nsvg__xformPoint(&path->pts[2 * i], &path->pts[2 * i + 1], pa->pts[2 * i], pa->pts[2 * i + 1], attr->xform);
        for ( ia = 0; ia < path->npts - 1; ia += 3 )
        {
          nsvg__curveBounds(bounds, &path->pts[2 * ia]);
          if ( ia )
          {
            v2 = nsvg__minf(path->bounds[0], bounds[0]);
            path->bounds[0] = v2;
            v3 = nsvg__minf(path->bounds[1], bounds[1]);
            path->bounds[1] = v3;
            v4 = nsvg__maxf(path->bounds[2], bounds[2]);
            path->bounds[2] = v4;
            v5 = nsvg__maxf(path->bounds[3], bounds[3]);
            path->bounds[3] = v5;
          }
          else
          {
            path->bounds[0] = bounds[0];
            path->bounds[1] = bounds[1];
            path->bounds[2] = bounds[2];
            path->bounds[3] = bounds[3];
          }
        }
        path->next = pa->plist;
        pa->plist = path;
      }
      else if ( path )
      {
        if ( path->pts )
          free(path->pts);
        free(path);
      }
    }
  }
}