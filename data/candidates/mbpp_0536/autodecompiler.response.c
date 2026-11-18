void func0(int *in, int in_length, int so_many, int *out, int *out_length) {
    int i, j;
    j = 0;
    for (i = 0; ; i += so_many) {
        if (i >= in_length) break;
        out[j++] = in[i];
    }
    *out_length = j;
}