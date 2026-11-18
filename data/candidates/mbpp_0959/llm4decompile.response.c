double func0(int *lst, int len) {
    int i;
    int sum = 0;
    for (i = 0; i < len; i++) {
        sum += lst[i];
    }
    return (double)sum / len;
}