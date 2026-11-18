void
AddArray4(float * restrict a, float * restrict b, int n)
{
    int i;

#pragma acc loop vector
    for (i = 0; ; i += 4) {
        if (i >= n) break;
#pragma acc cache(a[i])
#pragma acc cache(b[i])
        b[i] += a[i];
#pragma acc cache(a[i + 1])
#pragma acc cache(b[i + 1])
        b[i + 1] += a[i + 1];
#pragma acc cache(a[i + 2])
#pragma acc cache(b[i + 2])
        b[i + 2] += a[i + 2];
#pragma acc cache(a[i + 3])
#pragma acc cache(b[i + 3])
        b[i + 3] += a[i + 3];
    }
}