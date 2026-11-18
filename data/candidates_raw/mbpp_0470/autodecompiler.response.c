void test_fun(int x[], int N, int y[])
{
    int i;
    i = 0;
    while (i < N - 1) {
        y[i] = x[i] + x[i + 1];
        i = i + 1;
    }
}