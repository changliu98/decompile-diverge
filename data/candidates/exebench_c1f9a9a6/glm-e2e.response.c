int parse_uuid(const char *str, int *out) {
    int count = 0;
    int i;
    int val;
    int ret;

    // Initialize the output array to zeros
    for (i = 0; i < 4; i++) {
        out[i] = 0;
    }

    // Loop through each character in the string
    while (1) {
        char c = *str++;
        if (c == '\0') {
            break;
        }

        // Parse hexadecimal character
        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            val = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            val = c - 'A' + 10;
        } else {
            // If it's not a hex digit, check if it's a hyphen (or other allowed char)
            if (strchr("-", c) != NULL) {
                continue;
            } else {
                return 0;
            }
        }

        // If we haven't read 32 hex digits yet, store the current one
        if (count < 32) {
            out[count / 8] = (out[count / 8] << 4) + val;
        }
        count++;
    }

    // Return 1 if exactly 32 hex digits were parsed, 0 otherwise
    if (count == 32) {
        return 1;
    } else {
        return 0;
    }
}