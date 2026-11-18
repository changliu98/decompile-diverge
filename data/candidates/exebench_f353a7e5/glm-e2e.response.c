void strip(char *str) {
    if (str == NULL) {
        return;
    }

    char *result = str;
    int i = 1;

    // Mark duplicate characters with 0xFF
    while (str[i] != '\0') {
        for (int j = 0; j < i; j++) {
            if (result[j] == str[i]) {
                str[i] = (char)0xFF;
                break;
            }
        }
        i++;
    }

    int write_idx = 0;
    int read_idx = 0;

    // Find the first marked character
    i = 1;
    while (str[i] != '\0') {
        if (str[i] == (char)0xFF) {
            write_idx = i;
            while (str[i] == (char)0xFF) {
                i++;
            }
            read_idx = i;
            break;
        }
        i++;
    }

    // If no marked characters were found, return
    if (write_idx == 0) {
        return;
    }

    // Shift unmarked characters to the left
    while (str[read_idx] != '\0') {
        if (str[read_idx] == (char)0xFF) {
            read_idx++;
        } else {
            str[write_idx++] = str[read_idx];
            str[read_idx++] = (char)0xFF;
        }
    }
    str[write_idx] = '\0';
}