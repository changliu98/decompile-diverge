int func0(int n) {
    int result = 0;
    int power = 1;
    int temp = n;
    while (temp != 0) {
        int digit = temp % 10;
        temp = temp / 10;
        result = result + digit * power;
        power = power << 3;   // power *= 8
    }
    return result;
}