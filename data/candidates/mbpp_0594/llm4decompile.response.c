int func0(int *list1, int size) {
    int i;
    int first_even = -1;
    int first_odd = -1;

    for (i = 0; i < size; i++) {
        if (list1[i] % 2 == 0) {
            first_even = list1[i];
            break;
        }
    }

    for (i = 0; i < size; i++) {
        if (list1[i] % 2 != 0) {
            first_odd = list1[i];
            break;
        }
    }

    return first_even - first_odd;
}