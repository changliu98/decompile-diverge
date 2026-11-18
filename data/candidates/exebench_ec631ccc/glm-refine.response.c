void __cdecl lamda2x(double *lamda, double *x, double *h, double *boxlo)
{
    // x = H * lamda + boxlo
    // h is treated as a 3x3 matrix:
    // | h[0] h[1] h[2] |
    // | h[3] h[4] h[5] |
    // | h[6] h[7] h[8] |

    x[0] = (h[0] * lamda[0]) + (h[1] * lamda[1]) + (h[2] * lamda[2]) + boxlo[0];
    x[1] = (h[3] * lamda[0]) + (h[4] * lamda[1]) + (h[5] * lamda[2]) + boxlo[1];
    x[2] = (h[6] * lamda[0]) + (h[7] * lamda[1]) + (h[8] * lamda[2]) + boxlo[2];
}