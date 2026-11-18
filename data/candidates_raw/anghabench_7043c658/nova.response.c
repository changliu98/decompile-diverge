short func0(short *arr, int size, short max) {
    short func0 = 0;
    int i = 0;
    while (i < size) {
        if (arr[i] > func0) {
            func0 = arr[i];
        } else {
            i++;
        }
    }
    if (func0 == 0) {
        func0 = max;
    }
    return func0;
}