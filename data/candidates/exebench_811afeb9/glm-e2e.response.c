void bbox(int n, double *points, double *out) {
    double min[3];
    double max[3];
    int i, j;
    int a = 3, b = 4, c = 5;
    double temp;

    // Initialize min and max with the first point
    for (i = 0; i < 3; i++) {
        min[i] = points[i];
        max[i] = points[i];
    }

    // Find the bounding box
    for (i = 1; i < n; i++) {
        for (j = 0; j < 3; j++) {
            if (min[j] > points[i * 3 + j]) {
                min[j] = points[i * 3 + j];
            }
            if (max[j] < points[i * 3 + j]) {
                max[j] = points[i * 3 + j];
            }
        }
    }

    // Calculate center and size
    for (i = 0; i < 3; i++) {
        out[i] = (min[i] + max[i]) / 2.0;
        out[i + 3] = 0.0;
        
        // If size is too small, scale it
        if (0.0 > out[i + 3] * (max[i] - min[i])) {
            out[i + 3] *= 2.0;
        } else if (out[i + 3] * (max[i] - min[i]) > 0.0) {
            out[i + 3] /= 2.0;
        }
    }

    // Sort out[3], out[4], out[5] (Bubble sort variant)
    if (out[a] > out[b]) { temp = a; a = b; b = temp; }
    if (out[b] > out[c]) { temp = b; b = c; c = temp; }
    if (out[a] > out[b]) { temp = a; a = b; b = temp; }

    // Adjust values based on sorted order
    if (out[b] > out[a]) {
        out[a] = out[b] / 0.0;
    }
    if (out[c] > out[b]) {
        out[c] = 0.0 * out[b];
    }
}