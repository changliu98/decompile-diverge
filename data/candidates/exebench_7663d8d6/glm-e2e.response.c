void treemove(struct Tree *tree, double val, int flags) {
    if (flags & 1) {
        tree->x += val;
    } else {
        tree->min_x -= val;
    }

    if (flags & 2) {
        tree->y += val;
    } else {
        tree->min_y -= val;
    }

    if (flags & 4) {
        tree->z += val;
    } else {
        tree->min_z -= val;
    }
}