int func0(int array[], int length) {
    int max = -2147483648;
    int min = 2147483647;

    for (int i = 0; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }

    return max - min;
}