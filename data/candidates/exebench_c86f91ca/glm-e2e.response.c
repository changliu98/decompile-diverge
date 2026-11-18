void remove_dupc2(char *str) {
    int i = 0;
    int j;
    char is_valid;

    // Phase 1: Mark duplicate characters with 0xFF
    while (str[i] != '\0') {
        if (str[i] == (char)0xFF) {
            i++;
            continue;
        }
        j = i + 1;
        while (str[j] != '\0') {
            if (str[i] == str[j]) {
                str[j] = (char)0xFF;
            }
            j++;
        }
        i++;
    }

    // Phase 2: Find the first valid character to start the compaction
    j = 0;
    do {
        is_valid = (str[j] != '\0') && (str[j] != (char)0xFF);
        if (is_valid) {
            j++;
        }
    } while (is_valid);

    if (str[j] == '\0') {
        i = -1;
    } else {
        i = j;
    }

    // Phase 3: Compact the string by skipping 0xFF characters
    j = i + 1;
    while (str[j] != '\0') {
        if (str[j] != (char)0xFF) {
            i++;
            str[i] = str[j];
        }
        j++;
    }
    
    // Null-terminate the compacted string
    str[i + 1] = str[j];
}