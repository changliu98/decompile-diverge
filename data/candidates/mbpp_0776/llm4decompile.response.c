int func0(char *test_str)
{
    int len = strlen(test_str);
    int idx;
    int cnt = 0;

    for (idx = 1; idx < len - 1; idx++) {
        if (strchr("aeiou", test_str[idx]) == NULL) {
            if (strchr("aeiou", test_str[idx - 1]) != NULL ||
                strchr("aeiou", test_str[idx + 1]) != NULL) {
                cnt++;
            }
        }
    }

    if (strchr("aeiou", test_str[0]) == NULL &&
        strchr("aeiou", test_str[1]) != NULL) {
        cnt++;
    }

    if (strchr("aeiou", test_str[len - 1]) == NULL &&
        strchr("aeiou", test_str[len - 2]) != NULL) {
        cnt++;
    }

    return cnt;
}