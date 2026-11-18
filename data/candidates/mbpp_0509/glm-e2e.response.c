int func0(int n) {
    int result;
    int sum = 0;
    int count = 0;

    if (n % 2 == 0) {
        printf("Input is even");
        result = -1;
    } else {
        while (n >= 1) {
            count++;
            sum += n;
            n -= 2;
        }
        result = sum / count;
    }

    return result;
}