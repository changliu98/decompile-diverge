int func0(int n) {
    int a = 3;
    int b = 0;
    int c = 2;
    int res;

    if (n == 0) {
        res = 3;
    } else if (n == 1) {
        res = 3;
    } else if (n == 2) {
        res = 5;
    } else {
        int sum = 5;
        while (n > 2) {
            int next = a + b;
            sum += next;
            a = b;
            b = c;
            c = next;
            n--;
        }
        res = sum;
    }

    return res;
}