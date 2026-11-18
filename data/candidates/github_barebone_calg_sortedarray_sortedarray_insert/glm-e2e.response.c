int sortedarray_insert(sortedarray_t *sa, void *item) {
    int ret = 0;
    if (sa == NULL) {
        return 0;
    }

    int low = 0;
    int high = sa->size;
    int mid = 0;

    if (high > 1) {
        high = high;
    } else {
        high = 0;
    }

    while (low != high) {
        mid = (low + high) / 2;
        int cmp_res = sa->cmp(item, sa->data[mid]);
        
        if (cmp_res < 0) {
            high = mid;
        } else if (cmp_res > 0) {
            low = mid + 1;
        } else {
            break;
        }
    }

    if (sa->size > 0) {
        if (sa->cmp(item, sa->data[mid]) > 0) {
            mid++;
        }
    }

    if (sa->size + 1 > sa->capacity) {
        int new_capacity = sa->capacity * 2;
        void **new_data = realloc(sa->data, new_capacity * sizeof(void *));
        if (new_data == NULL) {
            return 0;
        }
        sa->data = new_data;
        sa->capacity = new_capacity;
    }

    memmove(sa->data + mid + 1, sa->data + mid, (sa->size - mid) * sizeof(void *));
    sa->data[mid] = item;
    sa->size++;
    
    return 1;
}