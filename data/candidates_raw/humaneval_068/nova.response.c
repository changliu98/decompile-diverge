static struct Range func0(int *list, int max, struct Range range) {
    int i, best, best_dist;
    best = best_dist = -1;
    for (i = 0; i < max; i++) {
        if (list[i] % 2 == 0) {
            if (list[i] < range.max && best == -1) {
                best = list[i];
            } else if (range.max - list[i] < best_dist) {
                best = list[i];
                best_dist = range.max - list[i];
            }
        }
    }
    if (best == -1) {
        range.min = range.max = 0;
    } else {
        range.min = best;
        range.max = best;
    }
    return range;
}