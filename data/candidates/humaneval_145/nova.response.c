int *func0(int *num, int n) {
    int *res = (int *)malloc(n * sizeof(int));
    int i = 0;
    while (i < n) {
        char str[10];
        sprintf(str, "%d", abs(num[i]));
        int j = 0;
        int sum = 0;
        while (j < strlen(str)) {
            if (j + 1 < strlen(str))
                sum += (str[j] - '0');
            else
                sum -= (str[j] - '0');
            j++;
        }
        res[i] = sum;
        i++;
    }
    int j = 0;
    while (j < n) {
        if (res[j] > res[j + 1]) {
            int temp = res[j];
            res[j] = res[j + 1];
            res[j + 1] = temp;
        }
        j++;
    }
    return res;
}