char *func0(const char *input) {
    int counts[10] = {0};
    const char *words[10] = {
        "one", "two", "three", "four", "five", 
        "six", "seven", "eight", "nine", "ten"
    };
    int out_idx = 0;
    const char *p = input;

    if (*p != '\0') {
        while (1) {
            int i = 0;
            char token[11];
            
            // Extract a word token (skip spaces, stop at space or end of string)
            while (p[i] != ' ' && p[i] != '\0') {
                token[i] = p[i];
                i++;
            }
            token[i] = '\0';
            
            // Compare token against the list of words
            for (int j = 0; j < 10; j++) {
                if (strcmp(token, words[j]) == 0) {
                    counts[j]++;
                    break;
                }
            }
            
            p += i + 1;
            if (*(p - 1) == '\0') {
                break;
            }
        }
    }

    // Build the output string based on counts
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < counts[i]; j++) {
            for (int k = 0; words[i][k] != '\0'; k++) {
                out[out_idx++] = words[i][k];
            }
            out[out_idx++] = ' ';
        }
    }

    // Trim trailing space if any
    if (out_idx > 0) {
        out[out_idx - 1] = '\0';
    } else {
        out[0] = '\0';
    }

    return out;
}