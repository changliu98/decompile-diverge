long search(long *head, const unsigned char *src, long src_len, const unsigned char *dst, long dst_len, long left, long right, long *best_off) {
    long best_len;
    long mid;
    const unsigned char *mid_src;
    long cmp_len;
    long len1;
    long len2;

    // Base case: if the range size is less than 2, evaluate the remaining 1 or 2 elements
    if (right - left < 2) {
        // Evaluate left candidate
        len1 = matchlen(src + head[left], dst - head[left], src_len, dst_len);
        
        // Evaluate right candidate
        len2 = matchlen(src + head[right], dst - head[right], src_len, dst_len);
        
        // Return the better of the two
        if (len1 > len2) {
            *best_off = head[left];
            best_len = len1;
        } else {
            *best_off = head[right];
            best_len = len2;
        }
        return best_len;
    }

    // Calculate the midpoint
    mid = left + (right - left) / 2;
    mid_src = src + head[mid];

    // Determine the maximum length we can compare without overrunning the source buffer
    cmp_len = src_len - head[mid];
    if (cmp_len < dst_len) {
        // Limited by the remaining source length
    } else {
        // Limited by the destination length
        cmp_len = dst_len;
    }

    // Compare the strings
    if (memcmp(mid_src, dst, cmp_len) < 0) {
        // The midpoint string is strictly less than the destination.
        // Search the right half.
        best_len = search(head, src, src_len, dst, dst_len, mid, right, best_off);
    } else {
        // The midpoint string is greater than or equal to the destination.
        // Search the left half.
        best_len = search(head, src, src_len, dst, dst_len, left, mid, best_off);
    }

    return best_len;
}