void func0(int *a, int *b, int *c, int len_a, int len_b, int len_c, int *range) {
    int i = 0, j = 0, k = 0;
    int min = 0x7fffffff;
    int res_i = 0, res_j = 0, res_k = 0;

    while (1) {
        if (i >= len_a || j >= len_b || k >= len_c) {
            break;
        }

        int min_val = ((a[i]) < (((b[j]) < (c[k]) ? (b[j]) : (c[k]))) ? (a[i]) : (((b[j]) < (c[k]) ? (b[j]) : (c[k]))));
        int max_val = ((a[i]) > (((b[j]) > (c[k]) ? (b[j]) : (c[k]))) ? (a[i]) : (((b[j]) > (c[k]) ? (b[j]) : (c[k]))));

        if (max_val - min_val < min) {
            res_i = i;
            res_j = j;
            res_k = k;
            min = max_val - min_val;
        }
        if (min == 0) {
            break;
        }

        if (min_val == a[i]) {
            i++;
        } else if (min_val == b[j]) {
            j++;
        } else {
            k++;
        }
    }

    range[0] = a[res_i];
    range[1] = b[res_j];
    range[2] = c[res_k];
}