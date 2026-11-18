void func0(int *arr) {
    int i, j, temp, flag;
    for (i = 1; i < SIZE; i++) {
        for (j = i; j > 0; j--) {
            if (arr[j] > arr[j - 1]) {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                flag = 0;
            } else {
                flag = 1;
            }
        }
        if (flag == 0) {
            continue;
        } else {
            break;
        }
    }
}