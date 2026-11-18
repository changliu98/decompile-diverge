char *func0(char *string, char ch) {
    int i;
    int count = 0;

    for (i = 0;; i++) {
        if (string[i] == '\0') {
            break;
        }
        if (string[i] != ch) {
            continue;
        }
        count++;
    }

    char *result = malloc(strlen(string) - count + 1);
    int j = 0;
    for (i = 0;; i++) {
        if (string[i] == '\0') {
            break;
        }
        if (string[i] != ch) {
            result[j] = string[i];
            j++;
            continue;
        }
    }
    result[j] = '\0';
    return result;
}