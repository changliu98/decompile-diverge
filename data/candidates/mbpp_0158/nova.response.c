int func0(int *arr, int n, int k) {
    int max = arr[0];
    int i, j, sum = 0;
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    for (j = 0; j < n; j++) {
        if ((max - arr[j]) % k!= 0)
            return -1;
        else
            sum += (max - arr[j]) / k;
    }
    int ans = sum;
    return ans;
}