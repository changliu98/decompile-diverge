double func0(int *values, int n)
{
    int i;
    int p = 0;

    for (i = 0; ; ++i) {
        if (i >= n) {
            break;
        }
        if (values[i] < 0) {
            ++p;
        }
    }

    double result = ((double)p / (double)n) * 100.0;

    return round(result) / 100.0;
}