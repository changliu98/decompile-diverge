int * func0(int array[], int length, int *resultSize) {
    int *unique = malloc(sizeof(int) * length);
    int size = 0;

    for (int i = 0; i < length; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (array[i] == unique[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[size++] = array[i];
        }
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (unique[i] > unique[j]) {
                int temp = unique[i];
                unique[i] = unique[j];
                unique[j] = temp;
            }
        }
    }

    *resultSize = size;

    return unique;
}