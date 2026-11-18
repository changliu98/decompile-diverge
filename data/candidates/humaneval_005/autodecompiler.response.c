int* func0(int* array, int n, int inter, int* size) {
    int sz;
    if (n > 0) {
        sz = (2 * n) - 1;
    } else {
        sz = 0;
    }
    *size = sz;
    int* result = (int*)malloc(sizeof(int) * sz);
    if (n > 0) {
        result[0] = array[0];
    }
    int ri = 1;
    int ai = 1;
    while (1) {
        if (ai < n) {
            result[ri++] = inter;
            result[ri++] = array[ai++];
        } else {
            break;
        }
    }
    return result;
}