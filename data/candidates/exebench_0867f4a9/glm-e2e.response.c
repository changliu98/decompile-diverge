int compter_mots(char *str, long *max_len) {
    char *p = strchr(str, '\0');
    int word_count = 0;
    int in_quote = 0;
    long current_len = 0;
    long max_word_len = 0;

    // Trim trailing spaces
    p--;
    while (*p == ' ') {
        *p = '\0';
        p--;
    }

    // Skip leading spaces
    p = str;
    while (*p == ' ') {
        p++;
    }

    // If the string isn't empty, count the first word
    if (*p != '\0') {
        word_count++;
    }

    // Parse the rest of the string
    while (*p != '\0') {
        if (*p == '"' || *p == '\'') {
            in_quote = !in_quote;
        } else if (*p == ' ' && !in_quote) {
            // Word boundary found
            if (current_len > max_word_len) {
                max_word_len = current_len;
            }
            current_len = 0;
            word_count++;

            // Skip consecutive spaces
            while (*p == ' ') {
                p++;
            }
            p--; // Step back so the outer loop's p++ positions correctly
        } else {
            current_len++;
        }
        p++;
    }

    // Check length of the last word
    if (current_len > max_word_len) {
        max_word_len = current_len;
    }

    *max_len = max_word_len;
    return word_count;
}