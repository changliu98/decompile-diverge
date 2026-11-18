char *build_ustar_entry_name(char *dst, const char *src, size_t src_len, const char *prefix) {
    int has_slash = 0;
    long remaining = 99;
    long prefix_len = 0;

    if (prefix != NULL) {
        prefix_len = strlen(prefix) + 2;
    }

    // If the source fits in the name field and no prefix is provided, just copy it.
    if (src_len < 100 && prefix == NULL) {
        strncpy(dst, src, src_len);
        dst[src_len] = '\0';
        return dst;
    }

    const char *src_end = src + src_len;

    // Strip trailing slashes
    while (src_end > src && src_end[-1] == '/') {
        src_end--;
        has_slash = 1;
    }

    // Strip trailing "/." sequences
    while (src_end > src + 1 && src_end[-1] == '.' && src_end[-2] == '/') {
        src_end -= 2;
        has_slash = 1;
    }

    if (has_slash) {
        remaining--;
    }

    const char *name_start = src_end - 1;

    // Find the beginning of the filename component (last segment after '/')
    while (name_start > src && *name_start != '/') {
        name_start--;
    }

    // If we landed on a '/', advance to the first character of the name
    if (*name_start == '/' && name_start < src_end - 1) {
        name_start++;
    }

    remaining -= prefix_len;

    // Adjust name_start if the name component is too long to fit in the remaining space
    if (src_end > name_start + remaining) {
        name_start = src_end - remaining;
    }

    remaining -= (src_end - name_start);

    const char *p = src;
    const char *prefix_end = p + 155;

    // Limit the prefix search area to 155 characters
    if (prefix_end > name_start) {
        prefix_end = name_start;
    }

    // Find the end of the prefix by walking backwards to the last '/' before name_start
    while (prefix_end > p && *prefix_end != '/') {
        prefix_end--;
    }

    // If we found a '/', advance past it for the prefix_end
    if (prefix_end < name_start && *prefix_end == '/') {
        prefix_end++;
    }

    const char *prefix_start = prefix_end;
    const char *prefix_limit = prefix_start + remaining;

    // Clamp the prefix_start bounds
    if (prefix_limit > name_start) {
        prefix_limit = name_start;
    }
    if (prefix_limit < prefix_start) {
        prefix_limit = prefix_start;
    }

    // Walk backwards from prefix_limit to find a clean directory boundary
    while (prefix_limit > prefix_start && *prefix_limit != '/') {
        prefix_limit--;
    }

    // If we found a '/', advance past it
    if (prefix_limit < name_start && *prefix_limit == '/') {
        prefix_limit++;
    }

    char *d = dst;

    // Copy the initial prefix part
    if (prefix_end > p) {
        strncpy(d, p, prefix_end - p);
        d += prefix_end - p;
    }

    // Copy the middle prefix part
    if (prefix_limit > prefix_start) {
        strncpy(d, prefix_start, prefix_limit - prefix_start);
        d += prefix_limit - prefix_start;
    }

    // Append the external prefix and a slash if provided
    if (prefix != NULL) {
        strcpy(d, prefix);
        d += strlen(prefix);
        *d++ = '/';
    }

    // Copy the final name component
    strncpy(d, name_start, src_end - name_start);
    d += src_end - name_start;

    // Add back the trailing slash if one was stripped originally
    if (has_slash) {
        *d++ = '/';
    }

    *d = '\0';

    return dst;
}