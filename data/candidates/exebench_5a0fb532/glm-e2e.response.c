char pop(char *arr, int *top) {
    char ret = (char)0xff; // -1 or 255 depending on signedness
    if (*top < 100 && *top >= 0) {
        ret = arr[*top];
        (*top)--;
    }
    return ret;
}