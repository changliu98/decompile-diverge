int *func0(int n) {
    int *arr = (int *)malloc(sizeof(int) * 2);
    arr[0] = 0;
    arr[1] = 0;
    int i = 1;
    while (1) {
        int temp = i;
        int sum = 0;
        int t = temp;
        while (t) {
            sum = sum * 10 + t % 10;
            t /= 10;
        }
        if (sum == i) {
            if (i % 2 == 0)
                arr[0]++;
            else
                arr[1]++;
        }
        i++;
    }
}