int foo(int *array) {
    int i, sum = 0;
    for (i = 0; i < 10; i++) {
        array[i] = i + 1;
    }
    return sum + i;
}