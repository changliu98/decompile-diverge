int toml_value_string(const char* str, void** out_ptr, char* out_buf) {
    char multiline = 0;
    *out_ptr = 0;
    
    if (!str) {
        return -1;
    }

    char quote = str[0];
    int len = strlen(str);

    if (quote != '\'' && quote != '"') {
        return -1;
    }

    const char* start;
    const char* end;

    if (str[1] == quote && str[2] == quote) {
        multiline = 1;
        start = str + 3;
        end = str + len - 3;

        if (start > end || end[0] != quote || end[1] != quote || end[2] != quote) {
            return -1;
        }

        if (*start == '\n') {
            start++;
        } else if (*start == '\r' && start[1] == '\n') {
            start += 2;
        }
    } else {
        start = str + 1;
        end = str + len - 1;

        if (start > end || *end != quote) {
            return -1;
        }
    }

    if (quote == '\'') {
        *out_ptr = norm_lit_str(start, end - start, out_buf, multiline, 0, 0);
    } else {
        *out_ptr = norm_basic_str(start, end - start, out_buf, multiline, 0, 0);
    }

    return *out_ptr != 0 ? 0 : -1;
}