void func0(int *arr, int len) {
    int i, j, k, temp, x, y, count_x, count_y;
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            count_x = count_y = 0;
            x = arr[i];
            y = arr[j];

            while (x > 0) {
                count_x += x & 1;
                x >>= 1;
            }

            while (y > 0) {
                count_y += y & 1;
                y >>= 1;
            }

            if (count_y < count_x || (count_y == count_x && arr[j] < arr[i])) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}