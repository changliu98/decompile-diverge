int fromDigits(int * digits, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        int minIndex = i + 1;
        for (j = i + 1; j < n; j++) {
            if (digits[i] < digits[j]) {
                int temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
            }
        }
    }

    int result = digits[0];
    for (i = 1; i < n; i++) {
        result = result * 10 + digits[i];
    }
    return result;
}