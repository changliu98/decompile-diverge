int func0(int a, int b) {
    int result;
    int gcd = 1;
    int i;

    if (a % b == 0) {
        result = b;
    } else {
        for (i = b / 2; i > 0; i--) {
            if (a % i == 0 && b % i == 0) {
                gcd = i;
                break;
            }
        }
        result = gcd;
    }

    return result;
}