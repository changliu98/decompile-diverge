void __cdecl nsvg__addPath(NSVGparser *p, char closed)
{
  float bounds[4];
  NSVGpath *path;
  NSVGattrib *attr;
  int i;

  attr = nsvg__getAttr(p);
  path = NULL;

  if (p->npts >= 4)
  {
    if (closed)
      nsvg__lineTo(p, p->pts[0], p->pts[1]);

    if (p->npts % 3 == 1)
    {
      path = (NSVGpath *)malloc(sizeof(NSVGpath));
      if (path)
      {
        memset(path, 0, sizeof(NSVGpath));
        path->pts = (float *)malloc(8 * p->npts);
        
        if (path->pts)
        {
          path->closed = closed;
          path->npts = p->npts;

          for (i = 0; i < p->npts; ++i)
            nsvg__xformPoint(&path->pts[2 * i], &path->pts[2 * i + 1], p->pts[2 * i], p->pts[2 * i + 1], attr->xform);

          for (i = 0; i < path->npts - 1; i += 3)
          {
            nsvg__curveBounds(bounds, &path->pts[2 * i]);
            if (i == 0)
            {
              path->bounds[0] = bounds[0];
              path->bounds[1] = bounds[1];
              path->bounds[2] = bounds[2];
              path->bounds[3] = bounds[3];
            }
            else
            {
              path->bounds[0] = nsvg__minf(path->bounds[0], bounds[0]);
              path->bounds[1] = nsvg__minf(path->bounds[1], bounds[1]);
              path->bounds[2] = nsvg__maxf(path->bounds[2], bounds[2]);
              path->bounds[3] = nsvg__maxf(path->bounds[3], bounds[3]);
            }
          }

          path->next = p->plist;
          p->plist = path;
        }
        else
        {
          free(path);
          path = NULL;
        }
      }
    }
  }
}