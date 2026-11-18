int sort_omegas(double *omegas) {
    int state = 0;
    double a, b, c, d;

    // Sort the first pair (omegas[0], omegas[1])
    if (omegas[0] > omegas[1]) {
        a = omegas[1];
        b = omegas[0];
        state = 1;
    } else {
        a = omegas[0];
        b = omegas[1];
    }

    // Sort the second pair (omegas[2], omegas[3])
    if (omegas[2] > omegas[3]) {
        c = omegas[3];
        d = omegas[2];
    } else {
        c = omegas[2];
        d = omegas[3];
    }

    // Sort the two pairs relative to each other based on their first elements (a and c)
    if (a > c) {
        omegas[0] = c;
        omegas[1] = a;
        if (state == 0) {
            state = 4;
        }
    } else {
        omegas[0] = a;
        omegas[1] = c;
    }

    // Sort the remaining elements (b and d)
    if (b > d) {
        omegas[3] = b;
        omegas[2] = d;
        if (state == 1) {
            state = 3;
        }
    } else {
        omegas[3] = d;
        omegas[2] = b;
        if (state == 1) {
            state = 5;
        }
    }

    // Final check and state update for the middle elements (omegas[1] and omegas[2])
    if (omegas[1] > omegas[2]) {
        double temp = omegas[1];
        omegas[1] = omegas[2];
        omegas[2] = temp;
        
        if (state == 4) {
            state = 2;
        } else if (state == 5) {
            state = 1;
        }
    } else {
        if (state == 4) {
            state = 1;
        } else if (state == 5) {
            state = 2;
        }
    }

    return state;
}