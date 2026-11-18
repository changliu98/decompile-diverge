int func0(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            count++;
        } else {
            int sum = 0;
            int num = abs(arr[i]);
            while (num >= 10) {
                sum += num % 10;
                num /= 10;
            }
            sum -= num;
            if (sum > 0) {
                count++;
            }
        }
    }
    return count;
}