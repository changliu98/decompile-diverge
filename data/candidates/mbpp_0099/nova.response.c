char *func0(int n) {
    static char bin[17];
    int x;
    int i;
    int j;

    i = 0;
    while (n > 0) {
        x = n % 2;
        bin[i++] = x + '0';
        n = n / 2;
    }
    bin[i] = '\0';
    j = 0;
    i = i - 1;
    while (j < i) {
        x = bin[j];
        bin[j] = bin[i];
        bin[i] = x;
        j++;
        i--;
    }
    return (bin);
}