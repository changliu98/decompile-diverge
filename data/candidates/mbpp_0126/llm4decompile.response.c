int func0(int a, int b) {
    int i, sum = 0;
    for (i = 1; i < ((a) < (b) ? (a) : (b)); i++) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
    }
    return sum;
}