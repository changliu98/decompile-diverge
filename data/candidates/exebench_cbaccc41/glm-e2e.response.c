bool clip(double *x, double *y, double *z, 
          double max_x, double max_y, double max_z, 
          double min_x, double min_y, double min_z) {
    bool changed = false;

    // Clip x
    if (*x > max_x) {
        *x = max_x;
        changed = true;
    } else if (*x < min_x) {
        *x = min_x;
        changed = true;
    }

    // Clip y
    if (*y > max_y) {
        *y = max_y;
        changed = true;
    } else if (*y < min_y) {
        *y = min_y;
        changed = true;
    }

    // Clip z
    if (*z > max_z) {
        *z = max_z;
        changed = true;
    } else if (*z < min_z) {
        *z = min_z;
        changed = true;
    }

    return changed;
}