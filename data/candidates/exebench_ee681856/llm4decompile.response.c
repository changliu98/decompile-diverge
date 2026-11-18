void c_saxpy(int n, double sa, double *sx, double *sy)
{
    int i, m;

    if (n <= 0 || sa == 0.0)
        return;

    m = n % 4;

    if (m > 0)
        for (i = 1; i <= m; i++)
            sy[i - 1] += sa * sx[i - 1];

    for (i = m + 1; i <= n; i += 4) {
        sy[i - 1] += sa * sx[i - 1];
        sy[i] += sa * sx[i];
        sy[i + 1] += sa * sx[i + 1];
        sy[i + 2] += sa * sx[i + 2];
    }
}