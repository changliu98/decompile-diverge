int func0(int *digits, int num) {
    int i = 0;
    while (num) {
        digits[i] = num % 10;
        num /= 10;
        i++;
    }
    return i;
}