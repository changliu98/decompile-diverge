void func0(int *arr, int size, int *new_arr) {
    int i, j, k, count = 0, index = 0;
    int temp = arr[0];
    for (i = 0; i < size; i++) {
        if (arr[i] == temp) {
            count++;
        } else {
            i++;
            temp = arr[i];
        }
    }
    for (j = 0; j < size; j++) {
        if (arr[j]!= temp) {
            new_arr[index++] = arr[j];
        }
    }
    for (k = 0; k < count; k++) {
        new_arr[index++] = temp;
    }
}