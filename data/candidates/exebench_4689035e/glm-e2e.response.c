void rgb2hsv(double r, double g, double b, double *h_out, double *s_out, double *v_out) {
    double h = 0.0;
    double s = 0.0;
    double max_val;
    double min_val;

    // Find max_val
    if (g > b) {
        max_val = g;
    } else {
        max_val = b;
    }
    if (r > max_val) {
        max_val = r;
    }

    // Find min_val
    if (g > b) {
        min_val = b;
    } else {
        min_val = g;
    }
    if (r < min_val) {
        min_val = r;
    }

    // Calculate Value (V)
    *v_out = max_val;

    // Calculate Saturation (S)
    if (max_val > 0.0) {
        s = (max_val - min_val) / max_val;
    }

    // Calculate Hue (H)
    if (s > 0.0) {
        double delta = max_val - min_val;
        double rc = (max_val - r) / delta;
        double gc = (max_val - g) / delta;
        double bc = (max_val - b) / delta;

        if (r == max_val) {
            h = bc - gc;
        } else if (g == max_val) {
            h = 2.0 + rc - bc;
        } else if (b == max_val) {
            h = 4.0 + gc - rc;
        }

        h *= 60.0;
        if (h < 0.0) {
            h += 360.0;
        }
    }

    // Output H and S
    *h_out = h / 360.0;
    *s_out = s;
}