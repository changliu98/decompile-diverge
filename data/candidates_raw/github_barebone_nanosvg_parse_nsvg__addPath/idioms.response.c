void nsvg_addpath(struct NSVGparser *ps, char closed)
{
  struct NSVGpath *path;
  struct NSVGattrib *attr;
  int i;
  float bounds[4];
  attr = nsvg_getattrib(ps);
  path = ((void *)0);
  if (ps->npts >= 4) {
    if (closed)
      nsvg_checkclosed(ps, ps->pts[0], ps->pts[1]);
    if (ps->npts % 3 == 1) {
      path = (struct NSVGpath *) nsvg_alloc(sizeof(NSVGpath));
      if (path == ((void *)0))
        goto fail;
      nsvg_initpath(path, 0);
      path->pts = (struct NSVGpoint *) nsvg_alloc(ps->npts * sizeof(NSVGpoint));
      if (path->pts == ((void *)0))
        goto fail;
      path->closed = closed;
      path->npts = ps->npts;
      for (i = 0; i < ps->npts; i++)
        nsvg_transformpt(&path->pts[i], &path->pts[i + 1], ps->pts[i].x, ps->pts[i].y, attr->xform);
      for (i = 0; i < path->npts - 1; i += 3) {
        nsvg_getptbounds(bounds, &path->pts[i]);
        if (i == 0) {
          path->bounds[0] = bounds[0];
          path->bounds[1] = bounds[1];
          path->bounds[2] = bounds[2];
          path->bounds[3] = bounds[3];
        } else {
          path->bounds[0] = nsvg_min(path->bounds[0], bounds[0]);
          path->bounds[1] = nsvg_min(path->bounds[1], bounds[1]);
          path->bounds[2] = nsvg_max(path->bounds[2], bounds[2]);
          path->bounds[3] = nsvg_max(path->bounds[3], bounds[3]);
        }
      }
      path->next = ps->plist;
      ps->plist = path;
    }
  }
  return;
 fail:
  if (path != ((void *)0)) {
    if (path->pts != ((void *)0))
      nsvg_free(path->pts);
    nsvg_free(path);
  }
  return;
}