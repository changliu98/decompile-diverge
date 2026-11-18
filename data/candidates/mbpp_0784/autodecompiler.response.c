int func0(int array[], int size) {
    int first_even = -1, first_odd = -1;
    for (int i = 0; ; i++) {
        if (i >= size) break;
        if (array[i] % 2 == 0 && first_even == -1) {
            first_even = array[i];
        }
        if (array[i] % 2 != 0 && first_odd == -1) {
            first_odd = array[i];
        }
        if (first_even != -1 && first_odd != -1) {
            break;
        }
    }
    return first_even * first_odd;
}