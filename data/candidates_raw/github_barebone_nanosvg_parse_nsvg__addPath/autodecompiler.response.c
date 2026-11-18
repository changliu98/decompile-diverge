void nsvg__addPath(struct NSVGparser* p, char closed)
{
    struct NSVGpath* path;
    struct NSVGattrib* attr = nsvg__getAttr(p);
    int i;

    if (p->npts < 5)
        return;


    if (closed)
        nsvg__lineTo(p, p->pts[0], p->pts[1]);

    if ((p->npts % 3) == 1)
    {

        path = (struct NSVGpath*)malloc(sizeof(struct NSVGpath));
        if (!path) goto error;
        memset(path, 0, sizeof(struct NSVGpath));

        path->coords = (float*)malloc((p->npts*2)*sizeof(float));
        if (!path->coords) goto error;
        path->closed = closed;
        path->npts = p->npts;

        for (i = 0; i < p->npts; i++)
            nsvg__xformPoint(&path->coords[i*2], &path->coords[i*2+1], &attr->xform, p->pts[i*2], p->pts[i*2+1]);


        for (i = 0; i < path->npts-1; i += 3)
        {
            float* p = &path->coords[i*2];
            struct NSVGrect cb;
            nsvg__curveBounds(&cb, p);
            if (i == 0) {
                path->bounds[0] = cb.x0;
                path->bounds[1] = cb.y0;
                path->bounds[2] = cb.x1;
                path->bounds[3] = cb.y1;
            } else {
                path->bounds[0] = nsvg__minf(path->bounds[0], cb.x0);
                path->bounds[1] = nsvg__minf(path->bounds[1], cb.y0);
                path->bounds[2] = nsvg__maxf(path->bounds[2], cb.x1);
                path->bounds[3] = nsvg__maxf(path->bounds[3], cb.y1);
            }
        }

        path->next = p->paths;
        p->paths = path;
    }
    else
    {
        goto error;
    }
    return;

error:
    if (path) {
        if (path->coords) free(path->coords);
        free(path);
    }
}