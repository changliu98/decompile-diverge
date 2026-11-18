static void func0(int a, int b, int c, int *out)
{
    if (b > c) {
        out[0] = a + c;
        out[1] = 0;
    } else {
        out[0] = a + b;
        out[1] = c - b;
    }
}