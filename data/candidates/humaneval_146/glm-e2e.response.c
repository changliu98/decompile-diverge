int func0(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 10) {
            int last_digit = arr[i] % 10;
            int first_digit = arr[i];
            while (first_digit >= 10) {
                first_digit /= 10;
            }
            if (first_digit % 2 == 1 && last_digit % 2 == 1) {
                count++;
            }
        }
    }
    return count;
}