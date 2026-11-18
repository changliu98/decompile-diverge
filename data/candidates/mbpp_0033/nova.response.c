int func0(int n) {
    int sum = 0;
    int i = 0;
    while (n!= 0) {
        int r = n % 2;
        int j = 1;
        int k = 0;
        while (k < i) {
            j = j * 10;
            k++;
        }
        sum = sum + r * j;
        n = n / 2;
        i++;
    }
    return sum;
}