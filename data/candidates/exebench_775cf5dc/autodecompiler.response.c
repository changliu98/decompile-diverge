void AddArray2(float *a, float *b, int n)
{
    int i;

    for (i = 0; i < n; i += 2) {
 b[i] += a[i];
 b[i + 1] += a[i + 1];
    }
}