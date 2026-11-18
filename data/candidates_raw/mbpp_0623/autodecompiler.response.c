void power(int *array, int length, int exponent, int *output) {
    int i = 0;
    while (1) {
        if (i < length) {
            output[i] = (int)pow((double)array[i], (double)exponent);
            i++;
        } else {
            return;
        }
    }
}