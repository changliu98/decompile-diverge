static void nsvg__addPath(NSVGparser* p, char closed) {
  int i;
  NSVGattrib* attr = nsvg__getAttr(p);
  NSVGpath* path = NULL;
  float bounds[4];
  if (p->pts < 4) return;
  if (closed) nsvg__lineTo(p, p->pt[0], p->pt[1]);
  if (p->pts % 3 != 1) return;
  path = (NSVGpath*)malloc(sizeof(NSVGpath));
  if (path == NULL) goto error;
  memset(path, 0, sizeof(NSVGpath));
  path->pts = (float*)malloc(p->pts * 2 * sizeof(float));
  if (path->pts == NULL) goto error;
  path->closed = closed;
  path->npts = p->pts;
  for (i = 0; i < p->pts; i++) {
    nsvg__xformPoint(&path->pts[i * 2], &path->pts[i * 2 + 1], p->pt[i * 2],
                     p->pt[i * 2 + 1], attr->xform);
  }
  for (i = 0; i < path->npts - 1; i += 3) {
    nsvg__curveBounds(bounds, &path->pts[i * 2]);
    if (i == 0) {
      path->bounds[0] = bounds[0];
      path->bounds[1] = bounds[1];
      path->bounds[2] = bounds[2];
      path->bounds[3] = bounds[3];
    } else {
      path->bounds[0] = nsvg__minf(path->bounds[0], bounds[0]);
      path->bounds[1] = nsvg__minf(path->bounds[1], bounds[1]);
      path->bounds[2] = nsvg__maxf(path->bounds[2], bounds[2]);
      path->bounds[3] = nsvg__maxf(path->bounds[3], bounds[3]);
    }
  }
  path->next = p->paths;
  p->paths = path;
  return;
error:
  if (path) {
    if (path->pts) free(path->pts);
    free(path);
  }
}