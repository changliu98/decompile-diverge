void func0(int a, int b, int *out, int *size)
{
    *size = 0;
    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int i = a; i <= b; i++) {
        if (i < 10 && i % 2 == 0) {
            out[(*size)++] = i;
        }
    }
}