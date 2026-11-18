int func0(int n) {
    char str[11];
    sprintf(str, "%d", n);
    int len = strlen(str);
    int i;
    for (i = len - 2; i >= 0; --i) {
        if (str[i] < str[i + 1]) {
            char temp[11];
            strcpy(temp, &str[i]);
            size_t templen = strlen(temp);
            char minchar = temp[1];
            size_t j;
            for (j = 1; j < templen; ++j) {
                if (temp[j] > temp[0] && temp[j] < minchar) {
                    minchar = temp[j];
                }
            }
            size_t k;
            for (k = 0; k < templen; ++k) {
                if (temp[k] == minchar) {
                    size_t l;
                    for (l = k; l < templen - 1; ++l) {
                        temp[l] = temp[l + 1];
                    }
                    temp[templen - 1] = '\0';
                    break;
                }
            }
            qsort(temp, strlen(temp), sizeof(char), compar);
            str[i] = minchar;
            strcpy(&str[i + 1], temp);
            int result = atoi(str);
            return result;
        }
    }
    return 0;
}