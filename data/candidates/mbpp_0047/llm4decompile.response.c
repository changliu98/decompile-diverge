int func0(int a, int b)
{
    int i;
    int result = 1;

    if (a == b) {
        return 1;
    }

    if (b - a > 4) {
        return 0;
    }

    for (i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
    }

    return result % 10;
}