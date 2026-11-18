int func0(struct Array *array, long long value) {
    if (array == NULL) {
        return 1;
    }

    if (array->length >= array->size) {
        size_t new_size = array->size + array->size / 2;
        long long *new_data = (long long *)realloc(array->data, new_size * sizeof(long long));
        if (new_data == NULL) {
            return 1;
        }
        array->data = new_data;
        array->size = new_size;
    }

    size_t index = array->length;
    array->length++;
    array->data[index] = value;
    sift_up(array, index);

    return 0;
}