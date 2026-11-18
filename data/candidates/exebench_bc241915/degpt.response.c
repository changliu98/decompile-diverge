void fb_hSetDirty(int *range_start, int *range_end, int new_start, int new_end)
{
    // If the dirty range is empty (start equals end), initialize it with the test range
    if (*range_start == *range_end) {
        *range_start = new_start;
        *range_end = new_end;
    } else {
        // Expand the dirty range to include the test range if it extends beyond current bounds
        if (new_start < *range_start) {
            *range_start = new_start;
        }
        if (*range_end < new_end) {
            *range_end = new_end;
        }
    }
}