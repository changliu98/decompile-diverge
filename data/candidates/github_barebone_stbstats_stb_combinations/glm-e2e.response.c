int stb_combinations(int n, int k, int ***out_mat) {
    int *c = (int *)calloc(k + 3, 4);
    int count = 0;
    int total = (int)(stb_factorial(n) / (stb_factorial(k) * stb_factorial(n - k)));
    int **mat = stb_allocmat(total, k, 4);

    for (int i = 1; i <= k; i++) {
        c[i] = i - 1;
    }
    c[k + 1] = n;
    c[k + 2] = 0;

    int j = k;
    visit:
    stb_visit(mat, k, count++);

    while (j > 0) {
        int x = j;
        c[j] = x;
        j--;
        stb_visit(mat, k, count++);
    }

    while (c[1] + 1 < c[2]) {
        c[1]++;
        stb_visit(mat, k, count++);

        while (j > 0) {
            int x = j;
            c[j] = x;
            j--;
            stb_visit(mat, k, count++);
        }
    }

    j = 2;
    c[j - 1] = 0;
    int x = c[j] + 1;

    while (x == c[j + 1]) {
        j++;
        c[j - 1] = 0;
        x = c[j] + 1;
    }

    if (j > k) {
        *out_mat = mat;
        free(c);
        return total;
    }

    c[j] = x;
    j--;
    goto visit;
}