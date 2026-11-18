int sorted_array_add(sorted_array_t *sa, void *item)
{
    int ret;
    unsigned int low, high, mid, idx;

    if (!sa) {
        ret = 0;
        goto end;
    }

    low = 0;
    high = sa->count;
    mid = 0;

    if (high > 1) {
        unsigned int old_high = high;
        while (1) {
            if (low == high) {
                break;
            }
            mid = (low + high) / 2;
            int cmp = sa->compare(item, sa->items[mid]);
            if (cmp < 0) {
                high = mid;
            } else if (cmp > 0) {
                low = mid + 1;
            } else {
                break;
            }
        }
        if (sa->count > 0 && sa->compare(item, sa->items[mid]) > 0) {
            mid++;
        }
    } else {
        mid = 0;
    }

    if (sa->count + 1 > sa->size) {
        unsigned int new_size = sa->size * 2;
        void **new_items = realloc(sa->items, sizeof(void *) * new_size);
        if (!new_items) {
            ret = 0;
            goto end;
        }
        sa->items = new_items;
        sa->size = new_size;
    } else {
        memmove(&sa->items[mid + 1], &sa->items[mid],
                sizeof(void *) * (sa->count - mid));
        sa->items[mid] = item;
        sa->count++;
        ret = 1;
    }
end:
    return ret;
}