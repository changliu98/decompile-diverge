void simplify(int *a, int *b) {
    int g = -1;
    int i;

    if (*a < *b && *a > 0) {
        i = *a;
    } else {
        if (*b > 0) {
            i = *b;
        } else {
            i = *a;
        }
    }

    while (i != 0) {
        if (*a % i == 0 && *b % i == 0) {
            g = i;
            i = 0;
        } else {
            if (i > 0) {
                i--;
            } else {
                i++;
            }
        }
    }

    if (g == -1) {
        g = g * g;
    }

    *a = *a / g;
    *b = *b / g;
}