int func0(int *a, int n) {
    int sum = 0, max = 0, i = 0;
    for (;;) {
        if (i >= n)
            break;
        sum += a[i];
        if (sum < 0)
            sum = 0;
        else if (sum > max)
            max = sum;
        i++;
    }
    return max;
}