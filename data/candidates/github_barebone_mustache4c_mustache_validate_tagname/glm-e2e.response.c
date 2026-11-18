int mustache_validate_tagname(const char *name, size_t len) {
    // If the tag name is exactly "." (a single dot), it is valid.
    if (len == 1 && name[0] == '.') {
        return 0;
    }

    // If the tag name starts or ends with a dot, it is invalid.
    if (name[0] == '.' || name[len - 1] == '.') {
        return -1;
    }

    // Iterate through each character in the tag name.
    for (size_t i = 0; i < len; i++) {
        // Whitespace characters (space, tab, vertical tab, form feed) are invalid.
        if (name[i] == ' ' || name[i] == '\t' || name[i] == '\v' || name[i] == '\f') {
            return -1;
        }

        // Consecutive dots ("..") are invalid.
        if (name[i] == '.' && i + 1 < len && name[i + 1] == '.') {
            return -1;
        }
    }

    // If none of the invalid conditions are met, the tag name is valid.
    return 0;
}