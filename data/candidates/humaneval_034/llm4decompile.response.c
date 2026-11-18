int * func0(int * l, int size, int * out_size)
{
    int * out = malloc((size_t)size * sizeof(int));
    int out_count = 0;
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < out_count; j++) {
            if (l[i] == out[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            out[out_count] = l[i];
            out_count++;
        }
    }
    for (int i = 0; i < out_count - 1; i++) {
        for (int j = i + 1; j < out_count; j++) {
            if (out[i] > out[j]) {
                int tmp = out[i];
                out[i] = out[j];
                out[j] = tmp;
            }
        }
    }
    *out_size = out_count;
    return out;
}