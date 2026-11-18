int int_range_lookup(int count, int64_t *ranges, int value) {
    if (count == 0) {
        return -1;
    }

    int low = 0;
    int high = count;
    int ret = -1;

    while (high > 1) {
        int mid = low + (high / 2);
        int64_t start_offset = ranges[mid];
        int64_t end_offset = ranges[mid + 1];
        int64_t range_len = end_offset - start_offset;
        int64_t range_end = start_offset + range_len;

        if (value < start_offset) {
            high = mid - low;
        } else if (value >= range_end) {
            int next = mid + 1;
            high = low + high - next;
            low = next;
        } else {
            ret = value - start_offset + end_offset;
            return ret;
        }
    }

    if (high > 0) {
        int64_t start_offset = ranges[low + 1];
        int64_t range_len = ranges[low + 2] - start_offset;
        int64_t range_start = ranges[low];

        if (value > range_start && value < range_start + range_len) {
            ret = value - range_start + start_offset;
            return ret;
        }
    }

    return -1;
}