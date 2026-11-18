int func0(int *arr, int size) {
    int i = 0;
    int flag;
    char c;
    while (1) {
        c = (i < size)? (arr[i]!= 0) : 0;
        if (c % 2 == 0) {
            break;
        }
        arr[i] = 0;
        i++;
    }
    int ret = (i < size)? 1 : 0;
    return ret;
}