void sort(int input[], int size, int output[]) {
    int first = input[0];
    int count_first = 0;
    int output_index = 0;

    for (int i = 0; ; i++) {
        if (i >= size) break;
        if (input[i] == first) count_first++;
        else continue;
    }

    for (int i = 0; ; i++) {
        if (i >= size) break;
        if (input[i] != first) output[output_index++] = input[i];
    }

    for (int i = 0; i < count_first; i++) {
        output[output_index++] = first;
    }
}