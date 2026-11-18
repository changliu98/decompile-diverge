int func0(int *dict, int size) {
    int i;
    int sum = 0;
    for (i = 0; i < size; i++) {
        sum += dict[i];
    }
    return sum;
}