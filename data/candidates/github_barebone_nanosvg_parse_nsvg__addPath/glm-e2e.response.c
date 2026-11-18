void nsvg__addPath(struct NSVGParser *p, char closed) {
    struct NSVGPath *path = NULL;

    if (p->npts < 4) {
        return;
    }

    if (closed) {
        // Close the path by moving to the first point
        nsvg__xformPoint(
            &p->matrix[0], &p->matrix[1], 
            p->pts[0], p->pts[1], 
            p->matrix
        );
    }

    // Check if the number of points is a multiple of 3 plus 1 (e.g., 4, 7, 10...)
    if (p->npts % 3 != 1) {
        return;
    }

    path = (struct NSVGPath *)nsvg__alloc(sizeof(struct NSVGPath));
    if (!path) {
        goto cleanup;
    }

    memset(path, 0, sizeof(struct NSVGPath));

    path->pts = (float *)nsvg__alloc(p->npts * 2 * sizeof(float));
    if (!path->pts) {
        goto cleanup;
    }

    path->closed = closed;
    path->npts = p->npts;

    // Transform and copy points
    for (int i = 0; i < p->npts; i++) {
        nsvg__xformPoint(
            &path->pts[i * 2], 
            &path->pts[i * 2 + 1], 
            p->pts[i * 2], 
            p->pts[i * 2 + 1], 
            p->matrix
        );
    }

    // Calculate bounding box
    for (int i = 0; i < path->npts - 1; i += 3) {
        float curveBounds[4];
        nsvg__curveBounds(curveBounds, &path->pts[i * 2]);

        if (i == 0) {
            path->bounds[0] = curveBounds[0];
            path->bounds[1] = curveBounds[1];
            path->bounds[2] = curveBounds[2];
            path->bounds[3] = curveBounds[3];
        } else {
            path->bounds[0] = nsvg__minf(path->bounds[0], curveBounds[0]);
            path->bounds[1] = nsvg__minf(path->bounds[1], curveBounds[1]);
            path->bounds[2] = nsvg__maxf(path->bounds[2], curveBounds[2]);
            path->bounds[3] = nsvg__maxf(path->bounds[3], curveBounds[3]);
        }
    }

    // Add to linked list
    path->next = p->paths;
    p->paths = path;
    return;

cleanup:
    if (path) {
        if (path->pts) {
            free(path->pts); // Assuming nsvg__alloc maps to malloc/calloc
        }
        free(path);
    }
}