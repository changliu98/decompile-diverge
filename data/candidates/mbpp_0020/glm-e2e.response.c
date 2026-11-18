bool func0(long n) {
    if (n % 2 == 0) {
        return false;
    }
    if (n == 1) {
        return true;
    }
    n = n + 1;
    long counter = 0;
    while (n % 2 == 0) {
        n = n / 2;
        counter++;
        if (counter == n) {
            return true;
        }
    }
    return false;
}