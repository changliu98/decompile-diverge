int func0(int A[], int n, int times) {
    int max_sum = -2147483648;
    int cur_sum = 0;
    int i = 0;
    while (1) {
        for (i = 0; i < n * times; ++i) {
            cur_sum += A[i % n];
            if (cur_sum > max_sum) {
                max_sum = cur_sum;
            }
            if (cur_sum < 0) {
                cur_sum = 0;
            }
        }
        break;
    }
    return max_sum;
}