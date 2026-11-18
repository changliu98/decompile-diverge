int INDMAXVAL(float *array, int start_index, int length) {
    int max_index = start_index;
    int i = start_index + 1;
    
    while (i <= length) {
        if (array[i] > array[max_index]) {
            max_index = i;
        }
        i++;
    }
    
    return max_index;
}