void func0(int *A, int *B, int *C, int p, int q, int r, int *res)
{
    int i, j, k;
    int diff = 2147483647;
    int res_i = 0, res_j = 0, res_k = 0;
    int minimum, maximum;

    i = 0;
    j = 0;
    k = 0;

    while (i < p && j < q && k < r) {
        minimum = (A[i] < B[j] ? (A[i] < C[k] ? A[i] : C[k]) : (B[j] < C[k] ? B[j] : C[k]));
        maximum = (A[i] > B[j] ? (A[i] > C[k] ? A[i] : C[k]) : (B[j] > C[k] ? B[j] : C[k]));

        if (maximum - minimum < diff) {
            res_i = i;
            res_j = j;
            res_k = k;
            diff = maximum - minimum;
        }

        if (diff == 0)
            break;

        if (A[i] == minimum)
            i++;
        else if (B[j] == minimum)
            j++;
        else
            k++;
    }

    res[0] = A[res_i];
    res[1] = B[res_j];
    res[2] = C[res_k];
}