void func0(const char *str, const char *chars_to_remove, char *out_str, char *out_status) {
    int len = strlen(str);
    char *filtered = malloc(len + 1);
    int f_idx = 0;
    int i = 0;

    // Filter out characters present in chars_to_remove
    while (str[i] != '\0') {
        char found = 0;
        const char *ptr = chars_to_remove;
        while (*ptr != '\0') {
            if (str[i] == *ptr) {
                found = 1;
                break;
            }
            ptr++;
        }
        if (!found) {
            filtered[f_idx++] = str[i];
        }
        i++;
    }
    filtered[f_idx] = '\0';

    // Check if the resulting string is a palindrome
    int filtered_len = strlen(filtered);
    char is_palindrome = 1;
    for (int j = 0; j < filtered_len / 2; j++) {
        if (filtered[j] != filtered[filtered_len - 1 - j]) {
            is_palindrome = 0;
            break;
        }
    }

    // Output results
    strcpy(out_str, filtered);
    strcpy(out_status, is_palindrome ? "Yes" : "No");

    free(filtered);
}