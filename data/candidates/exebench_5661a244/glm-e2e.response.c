long FAT_parse_directory(const char *path, size_t length, size_t *pos1, size_t *pos2) {
    // Skip the first part of the path until a '\' is found or the end is reached
    while (*pos1 < length) {
        if (path[*pos1] == '\\') {
            break;
        }
        (*pos1)++;
    }

    // If we reached the end of the string without finding a '\', return 0
    if (*pos1 == length) {
        return 0;
    }

    // Skip the '\' character
    (*pos1)++;

    // Set the start of the second part to be right after the '\'
    *pos2 = *pos1 + 1;

    // Skip the second part of the path until a '\' is found or the end is reached
    while (*pos2 < length) {
        if (path[*pos2] == '\\') {
            break;
        }
        (*pos2)++;
    }

    // Return the length of the second part
    return *pos2 - *pos1;
}