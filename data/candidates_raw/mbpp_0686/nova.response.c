char *func0(int *arr, int n) {
    int i, j, k, l, m, p, q;
    int *count;
    char *str;

    i = j = k = 0;
    while (j < n) {
        p = 0;
        for (l = 0; l < i; l++) {
            if (arr[l] == arr[j]) {
                count[l]++;
                p = 1;
                break;
            }
        }
        if (p == 0) {
            arr[i] = arr[j];
            count[i] = 1;
            i++;
        }
        j++;
    }

    str = (char *)malloc(1000 * sizeof(char));
    str[0] = '\0';
    strcat(str, "{");
    for (m = 0; m < i; m++) {
        char temp[100];
        sprintf(temp, "%d(%d)", arr[m], count[m]);
        strcat(str, temp);
        if (m < i - 1)
            strcat(str, ",");
    }
    strcat(str, "}");

    return str;
}