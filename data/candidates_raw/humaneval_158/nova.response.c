char *func0(char **str, int n) {
    char *func0 = " ";
    int i = 0, j = 0;
    while (j < n) {
        char temp[256] = {0};
        int k = 0;
        while (1) {
            if (str[j][k] == 0) {
                break;
            }
            if (strchr(temp, str[j][k]) == NULL) {
                temp[strlen(temp)] = str[j][k];
                temp[strlen(temp) + 1] = 0;
                i++;
            }
            k++;
        }
        if (i > j) {
            if (i == j && strcmp(str[j], func0) < 0) {
                func0 = str[j];
            }
        }
        j++;
    }
    return func0;
}