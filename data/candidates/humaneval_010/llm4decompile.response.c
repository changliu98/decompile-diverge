char *func0(char *str)
{
    int i, j, k, len;
    char *new_str;
    int is_palindrome;

    len = strlen(str);
    new_str = (char *)malloc((size_t)(len * 2 + 1));
    if (new_str == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        is_palindrome = 1;
        for (j = 0; j < (len - i) / 2; j++) {
            if (str[i + j] != str[len - 1 - j]) {
                is_palindrome = 0;
                break;
            }
        }

        if (is_palindrome) {
            strncpy(new_str, str, (size_t)len);
            for (k = 0; k < i; k++) {
                new_str[len + k] = str[i - k - 1];
            }
            new_str[len + i] = '\0';

            return new_str;
        }
    }

    strncpy(new_str, str, (size_t)len);
    for (j = 0; j < len; j++) {
        new_str[len + j] = str[len - j - 1];
    }
    new_str[len * 2] = '\0';

    return new_str;
}