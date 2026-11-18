void func0(float *l, int size, float *out)
{
    int i, j;
    float *even;
    int even_count = 0;
    float temp;

    even = (float *)malloc((size / 2 + 1) * sizeof(float));

    for (i = 0; i < size; i += 2) {
        even[even_count] = l[i];
        even_count++;
    }

    for (i = 0; i < even_count - 1; i++) {
        for (j = 0; j < even_count - i - 1; j++) {
            if (even[j] > even[j + 1]) {
                temp = even[j];
                even[j] = even[j + 1];
                even[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            out[i] = even[i / 2];
        } else {
            out[i] = l[i];
        }
    }

    free(even);
}