void cJSON_Minify(char *json) {
    if (json == NULL) {
        return;
    }

    char *into = json;
    const char *ptr = json;

    while (*ptr != '\0') {
        char c = *ptr;

        // Skip whitespace characters ('\t', '\n', '\r', ' ')
        if (c == '\t' || c == '\n' || c == '\r' || c == ' ') {
            ptr++;
        } 
        // Handle string literals
        else if (c == '\"') {
            minify_string(&ptr, &into);
        } 
        // Handle comments
        else if (c == '/') {
            if (*(ptr + 1) == '/') {
                skip_oneline_comment(&ptr);
            } else if (*(ptr + 1) == '*') {
                skip_multiline_comment(&ptr);
            } else {
                // If it's just a slash, copy it over
                *into++ = *ptr++;
            }
        } 
        // Copy any other character directly
        else {
            *into++ = *ptr++;
        }
    }

    // Null-terminate the minified string
    *into = '\0';
}