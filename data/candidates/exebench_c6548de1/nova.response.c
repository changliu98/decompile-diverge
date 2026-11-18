void swap(struct Array *array) {
    int min_index = 0;
    int max_index = array->length;

    int min = array->array[0];
    for (int i = 0; i < 10; i++) {
        if (array->array[i] < min) {
            min_index = i;
        }
    }

    int max = 0;
    int max_2 = array->array[0];
    for (int i = 0; i < 10; i++) {
        if (array->array[i] > max_2) {
            max = i;
        }
    }

    array->array[min_index] = array->array[min_index] + array->array[max];
    array->array[min_index] = array->array[min_index] - array->array[max];
    array->array[min_index] = array->array[min_index] - array->array[max];

    array->array[max] = array->array[max] + array->array[min_index];
    array->array[max] = array->array[max] - array->array[min_index];
    array->array[max] = array->array[max] - array->array[min_index];
}