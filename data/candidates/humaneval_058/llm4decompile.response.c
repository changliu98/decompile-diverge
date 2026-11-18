int *func0(int *l1, int size1, int *l2, int size2, int *out_size)
{
    int *out = malloc((size_t)size1 * sizeof(int));
    int i, j, k = 0, exists_in_out;
    for (i = 0; i < size1; i++) {
        exists_in_out = 0;
        for (j = 0; j < k; j++) {
            if (out[j] == l1[i]) {
                exists_in_out = 1;
                break;
            }
        }
        if (exists_in_out)
            continue;
        for (j = 0; j < size2; j++) {
            if (l1[i] == l2[j]) {
                out[k] = l1[i];
                k++;
                break;
            }
        }
    }
    for (i = 0; i < k - 1; i++) {
        for (j = 0; j < k - i - 1; j++) {
            if (out[j] > out[j + 1]) {
                int tmp = out[j];
                out[j] = out[j + 1];
                out[j + 1] = tmp;
            }
        }
    }
    *out_size = k;
    return out;
}