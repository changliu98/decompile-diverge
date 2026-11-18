void factorial(double *arr) {
    arr[0] = 1.0;
    for (int i = 0; i < 20; i++) {
        arr[i + 1] = (double)(i + 1) * arr[i];
    }
}