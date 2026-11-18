void numpar(double *x,int *n,int *num)
{
    int i,j,k,numpar;
    int jump[50];
    double eps,x1,x2;

    numpar = -1;
    eps = 1e-6;
    i = -1;
    while (i < *n-1) {
        i++;
        for (j=0; j<=numpar-1; j++)
            if (i == jump[j])
                i++;
        x1 = x[i];
        k = i+1;
        while (k < *n) {
            for (j=0; j<=numpar-1; j++)
                if (k == jump[j])
                    k++;
            x2 = x[k];
            if (x1-x2 < 0) {
                if (-(x1-x2) < eps) {
                    jump[numpar+1] = k;
                    numpar++;
                    *num = *num-1;
                }
            } else {
                if (x1-x2 < eps) {
                    jump[numpar+1] = k;
                    numpar++;
                    *num = *num-1;
                }
            }
            k++;
        }
    }
}