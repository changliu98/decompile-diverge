int *func0(char *str, int *size) {
    int *arr = NULL;
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0;
    char buf[3];
    memset(buf, 0, sizeof(buf));
    do {
        n = strlen(str);
        arr = (int *)malloc((n + 1) * sizeof(int));
        strcpy(arr, str);
        do {
            if (strcmp(buf, "000") == 0) {
                if (k == l) {
                    if (l > 0) {
                        m = l * 2;
                    } else {
                        m = 4;
                    }
                } else {
                    l = m;
                }
                arr = (int *)realloc(arr, (l + 1) * sizeof(int));
                arr[i++] = 1;
                strcpy(buf, "000");
            }
            if (strcmp(buf, "001") == 0) {
                if (k == l) {
                    if (l > 0) {
                        m = l * 2;
                    } else {
                        m = 4;
                    }
                } else {
                    l = m;
                }
                arr = (int *)realloc(arr, (l + 1) * sizeof(int));
                arr[i++] = 2;
                strcpy(buf, "000");
            }
        } while (1);
    } while (1);
    *size = i;
    return arr;
}