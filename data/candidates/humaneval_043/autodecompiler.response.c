int func0(int *array, int size) {
    char found;
    int j, i = 0;

    while (1) {
        if (i >= size) break;

        for (j = i + 1; j < size; j++) {
            if (array[i] + array[j] == 0) {
                found = 1;
                goto end;
            }
        }

        i++;
    }

    end:
    return found & 1;
}