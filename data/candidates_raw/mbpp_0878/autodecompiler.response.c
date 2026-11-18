int test_subset(int *tuple, int tuple_size, int *set, int set_size) {
    int i, j;
    char found;

    for (i = 0; i < tuple_size; i++) {
        found = 0;
        for (j = 0; j < set_size; j++) {
            if (tuple[i] == set[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }

    return 1;
}