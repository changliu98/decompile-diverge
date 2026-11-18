void func0(char *str, int reverse) {
    int len = strlen(str);
    int n = (len + 2) / 3;
    int i = 0;
    while (i < n) {
        int j = i * 3;
        int k = (i + 1) * 3 - 1;
        if (j + 3 > len) {
            k = len;
        }
        char temp[4];
        strncpy(temp, str + j, k - j);
        temp[k - j] = '\0';
        if (k - j == 3) {
            if (reverse) {
                char temp2[4];
                strncpy(temp2, temp, 3);
                temp2[3] = '\0';
                strncpy(temp, temp2, 3);
            }
        } else {
            strncpy(str + j, temp, k - j);
        }
        i++;
    }
}