int sort_omegas(double *arr) {
    int i, j, k;
    double temp;
    for (i = 0; i < 2; i++) {
        if (arr[0] > arr[1]) {
            temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
            k = 1;
        } else {
            temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
            k = 0;
        }
        if (arr[1] > arr[2]) {
            temp = arr[1];
            arr[1] = arr[2];
            arr[2] = temp;
            if (k == 1) {
                k = 3;
            } else {
                k = 4;
            }
        }
        if (arr[0] > arr[1]) {
            temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
            if (k == 0) {
                k = 1;
            } else {
                k = 2;
            }
        }
        if (k == 4) {
            k = 1;
        }
        if (k == 5) {
            k = 2;
        }
    }
    return k;
}