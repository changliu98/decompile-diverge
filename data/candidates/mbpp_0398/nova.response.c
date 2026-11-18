int func0(int *digits, int digitsSize) {
    int sum = 0;
    int i = 0;
    while (1) {
        if (i < digitsSize) {
            int num = digits[i];
            if (num < 0) {
                num = 0 - num;
            }
            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }
            i++;
        } else {
            break;
        }
    }
    return sum;
}