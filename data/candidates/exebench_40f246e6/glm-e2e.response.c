float interp_tri(TriData *tri, float u, float v, int flip) {
    double u_d = (u < 0.0) ? 0.0 : (u > 1.0 ? 1.0 : (double)u);
    double v_d = (v < 0.0) ? 0.0 : (v > 1.0 ? 1.0 : (double)v);

    if (u_d == 0.0) {
        if (v_d == 0.0) {
            return tri->v[0];
        } else if (v_d == 1.0) {
            return tri->v[2];
        }
    } else if (u_d == 1.0) {
        if (v_d == 0.0) {
            return tri->v[1];
        } else if (v_d == 1.0) {
            return tri->v[3];
        }
    }

    double v0, v1, v2, v3;
    if (flip > 0) {
        v0 = tri->v[0];
        v1 = tri->v[1];
        v2 = tri->v[3];
        v3 = tri->v[2];
    } else {
        u_d = 1.0 - u_d;
        v0 = tri->v[1];
        v1 = tri->v[0];
        v2 = tri->v[2];
        v3 = tri->v[3];
    }

    if (v_d >= u_d) {
        // Swap logic
        double tmp = v0;
        v0 = v2;
        v2 = tmp;
        
        tmp = v1;
        v1 = v3;
        v3 = tmp;

        u_d = 1.0 - u_d;
        v_d = 1.0 - v_d;
    }

    double a = v0 + (v1 - v0) * u_d;
    double b = v0 + (v3 - v0) * u_d;
    return (float)(a + (b - a) * (v_d / u_d));
}