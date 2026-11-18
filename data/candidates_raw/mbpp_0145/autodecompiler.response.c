int range(int array[], int length) {
    int min = array[0];
    int max = array[0];

    for (int i=1; i<length; i++) {
        if (array[i] < min) {
            min = array[i];
        }
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max - min;
}