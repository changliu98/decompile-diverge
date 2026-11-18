int func0(struct Array *array, int key) {
    int low, high, mid, result;

    if (isSorted(array)) {
        low = array->length - 1;
    } else {
        low = 0;
    }

    high = low;
    mid = -1;

    while (low + 1 < high) {
        mid = low + (high - low) / 2;

        if (key > array->array[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    if (high < low || array->array[high]!= key) {
        result = -low - 1;
    } else {
        result = high;
    }

    return result;
}