long sort_omegas(double *arr) {
    long state = 0;
    double a, b, c, d, temp;

    // Sort the first pair (arr[0], arr[1])
    if (arr[0] > arr[1]) {
        a = arr[1];
        b = arr[0];
        state = 1;
    } else {
        a = arr[0];
        b = arr[1];
    }

    // Sort the second pair (arr[2], arr[3])
    if (arr[2] > arr[3]) {
        c = arr[3];
        d = arr[2];
    } else {
        c = arr[2];
        d = arr[3];
    }

    // Merge the smaller elements of both pairs into arr[0] and arr[1]
    if (a > c) {
        arr[0] = c;
        arr[1] = a;
        if (state == 0) {
            state = 4;
        }
    } else {
        arr[0] = a;
        arr[1] = c;
    }

    // Merge the larger elements of both pairs into arr[2] and arr[3]
    if (b > d) {
        arr[3] = b;
        arr[2] = d;
        if (state == 1) {
            state = 3;
        }
    } else {
        arr[3] = d;
        arr[2] = b;
        if (state == 1) {
            state = 5;
        }
    }

    // Final sort: ensure arr[1] and arr[2] are ordered
    if (arr[1] > arr[2]) {
        temp = arr[1];
        arr[1] = arr[2];
        arr[2] = temp;
        
        if (state == 4) {
            state = 2;
        }
        if (state == 5) {
            state = 1;
        }
    } else {
        if (state == 4) {
            state = 1;
        }
        if (state == 5) {
            state = 2;
        }
    }

    return state;
}