void nsvg__addPath(NSVGparser* p, char closedFlag)
{
    NSVGpath* path;
    NSVGattrib* attr = nsvg__getAttr(p);
    float bounds[4];
    int i;

    if (p->npts < 4)
        return;

    if (closedFlag)
        nsvg__lineTo(p, p->pts[0], p->pts[1]);

    if (p->npts % 3 != 1)
        return;

    path = (NSVGpath*)malloc(sizeof(NSVGpath));
    if (path == NULL)
        goto error;
    memset(path, 0, sizeof(NSVGpath));

    path->pts = (float*)malloc(p->npts * 2 * sizeof(float));
    if (path->pts == NULL)
        goto error;

    path->closed = closedFlag;
    path->npts = p->npts;

    for (i = 0; i < p->npts; i++)
        nsvg__xformPoint(&path->pts[i * 2], &path->pts[i * 2 + 1], p->pts[i * 2], p->pts[i * 2 + 1], attr->xform);

    for (i = 0; i < path->npts - 1; i += 3) {
        nsvg__curveBounds(bounds, &path->pts[i * 2], &path->pts[i * 2 + 1], &path->pts[i * 2 + 2], &path->pts[i * 2 + 3], &path->pts[i * 2 + 4], &path->pts[i * 2 + 5]);
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

    path->next = p->plist;
    p->plist = path;

    return;

error:
    if (path != NULL) {
        if (path->pts != NULL)
            free(path->pts);
        free(path);
    }
}