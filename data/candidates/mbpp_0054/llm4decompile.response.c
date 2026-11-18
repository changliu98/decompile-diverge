void func0(int *my_list, int n) {
    int max_value = 0;
    for (int i = 0; i < n; i++) {
        if (my_list[i] > max_value) {
            max_value = my_list[i];
        }
    }

    int *counts = (int *)malloc(sizeof(int) * (max_value + 1));
    for (int j = 0; j < max_value + 1; j++) {
        counts[j] = 0;
    }

    for (int i = 0; i < n; i++) {
        counts[my_list[i]]++;
    }

    int pos = 0;
    for (int j = 0; j < max_value + 1; j++) {
        for (int a = 0; a < counts[j]; a++) {
            my_list[pos] = j;
            pos++;
        }
    }

    free(counts);
}