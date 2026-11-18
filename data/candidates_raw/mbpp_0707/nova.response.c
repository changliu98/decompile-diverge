int func0(int n) {
    n++;
    int i = 2, x, y;
    x = n / i;
    while (1) {
        if (i > n) {
            x = n / i;
            x = x * i + (n % i);
            if (x % 2)
                x += n % i;
            i *= 2;
        } else
            break;
    }
    return x;
}