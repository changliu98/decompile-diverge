corresponds to 0x40a0

char* func0(char* str) {
    int len = strlen(str);
    int i = 0;
    int current_len = 0;
    int max_len = 0;
    int start = -1;

    while (i < len) {
        if (str[i] == ' ') {
            if (current_len % 2 == 0) {
                if (max_len < current_len) {
                    max_len = current_len;
                    start = i - current_len;
                }
            }
            current_len = 0;
        } else {
            current_len++;
        }
        i++;
    }

    // Check the last word
    if (current_len % 2 == 0) {
        if (max_len < current_len) {
            max_len = current_len;
            start = i - current_len;
        }
    }

    if (start == -1) {
        return "";
    } else {
        strncpy(result, str + start, max_len);
        result[max_len] = '\0';
        return result;
    }
}