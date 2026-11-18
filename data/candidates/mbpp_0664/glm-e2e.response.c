int func0(int n) {
    int result;
    int sum = 0;
    int count = 0;

    if (n % 2 != 0) {
        printf("n must be even");
        result = -1;
    } else {
        while (n >= 2) {
            count++;
            sum += n;
            n -= 2;
        }
        result = sum / count;
    }

    return result;
}