void
get_borders(double *y, int *n, int *nb)
{
    int b[*n];
    int k = -1;
    int j = 0;
    int i = 0;
    int l = -1;
    double d = 0;

    while(k < *n - 1) {
        k++;
        j = 0;
        while(j < l) {
            if(b[j] == k) {
                k++;
            }
            j++;
        }
        i = k + 1;
        while(i < *n) {
            j = 0;
            while(j < l) {
                if(b[j] == i) {
                    i++;
                }
                j++;
            }
            d = y[k] - y[i];
            if(d < 0) {
                d *= -1;
            }
            if(d == 0) {
                l++;
                b[l] = i;
                *nb = *nb - 1;
            }
            i++;
        }
    }
}