int func0(int array[], int size, int sum, int *triplet) {
    for (int i = 0; i < size - 2; i++) {
        for (int j = i + 1; j < size - 1; j++) {
            for (int k = j + 1; k < size; k++) {
                if (array[i] + array[j] + array[k] == sum) {
                    triplet[0] = array[i];
                    triplet[1] = array[j];
                    triplet[2] = array[k];
                    char found = 1;
                    goto done;
                }
            }
        }
    }

    char found = 0;

done:
    return found;
}