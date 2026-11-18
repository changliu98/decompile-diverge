int func0(char *string, char **array, int max) {
    int count = 0;
    char *p;
    int i;

    if (string == NULL || *string == '\0') {
        return -1;
    }

    while (1) {
        while (*string =='') {
            string++;
        }
        if (*string == '\0') {
            break;
        }
        p = string;
        while (*string!='' && *string!= '\0') {
            string++;
        }
        if (*string == '\0') {
            break;
        }
        array[count++] = p;
        string = strchr(string, '/');
        if (string == NULL) {
            break;
        }
        *string = '\0';
        string++;
    }
    return count;
}