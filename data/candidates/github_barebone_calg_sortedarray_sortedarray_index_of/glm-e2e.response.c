int sortedarray_index_of(struct SortedArray *array, const void *value) {
    int result = -1;
    
    if (array == NULL) {
        return -1;
    }

    uint32_t left = 0;
    uint32_t right = array->size;
    uint32_t mid = 0;

    // If size > 1, right = size, else right = 0
    if (array->size > 1) {
        right = array->size;
    } else {
        right = 0;
    }

    while (left != right) {
        mid = (left + right) / 2;
        
        int cmp_result = array->cmp(value, array->data[mid]);
        
        if (cmp_result < 0) {
            right = mid;
        } else if (cmp_result > 0) {
            left = mid + 1;
        } else {
            result = mid;
            return result;
        }
    }

    result = -1;
    return result;
}