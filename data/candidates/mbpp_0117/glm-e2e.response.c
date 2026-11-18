char *func0(char **arr, int n) {
    static char res[256];
    char buf[100];
    int i;

    strcpy(res, "[");
    for (i = 0; i < n; i += 2) {
        double a = atof(arr[i]);
        double b = atof(arr[i + 1]);
        snprintf(buf, 100, "(%.1f, %.1f)", a, b);
        strcat(res, buf);
        if (i < n - 2) {
            strcat(res, ", ");
        }
    }
    strcat(res, "]");
    return res;
}