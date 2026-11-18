void StrBracketMatch(const char *str, int *arr, int *out_len, int *out_pos, int max_len) {
    int depth = 0;
    int i = 0;
    int count = 0;
    char quote = 0;

    while (str[i] != '\0') {
        if (quote != 0) {
            if (str[i] == quote) {
                if (i == 0 || str[i - 1] != '\\') {
                    quote = 0;
                }
            }
        } else {
            if (str[i] == '\'' || str[i] == '"') {
                quote = str[i];
            } else if (str[i] == '(') {
                depth++;
                if (depth == 1) {
                    if (arr != NULL && (max_len < 0 || count < max_len)) {
                        arr[count++] = i;
                    }
                }
            } else if (str[i] == ')') {
                depth--;
                if (depth == 0) {
                    break;
                }
            } else if (str[i] == ',') {
                if (depth == 1) {
                    if (arr != NULL && (max_len < 0 || count < max_len)) {
                        arr[count++] = i;
                    }
                }
            }
        }
        i++;
    }

    if (str[i] == '\0') {
        if (out_len != NULL) {
            *out_len = -1;
        }
        if (out_pos != NULL) {
            *out_pos = -1;
        }
    } else {
        if (arr != NULL && (max_len < 0 || count < max_len)) {
            arr[count++] = i;
        }
        if (out_len != NULL) {
            *out_len = count - 1;
        }
        if (out_pos != NULL) {
            *out_pos = i;
        }
    }
}