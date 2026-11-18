int findMaxK(int *c, int *b, int n) {
    qsort(c, (size_t)n, sizeof(int), compare);
    qsort(b, (size_t)n, sizeof(int), compare);

    int i = 1, j = 0;
    int max_k = 1, current_k = 1;

    while (1) {
        if (i >= n || j >= n) break;

        if (c[i] <= b[j]) {
            current_k++;
            i++;

            if (current_k > max_k) {
                max_k = current_k;
            }
        } else {
            current_k--;
            j++;
        }
    }

    return max_k;
}