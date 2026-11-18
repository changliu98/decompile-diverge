char* func0(int num) {
    char temp[6];
    sprintf(temp, "%d", num);

    int sum = 0;
    for (int i = 0; temp[i] != '\0'; i++) {
        sum += temp[i] - '0';
    }

    char *res = (char *)malloc(33);
    int idx = 0;

    if (sum == 0) {
        res[idx++] = '0';
    } else {
        while (sum > 0) {
            res[idx++] = (sum % 2) + '0';
            sum /= 2;
        }
    }
    res[idx] = '\0';

    for (int i = 0; i < idx / 2; i++) {
        char t = res[i];
        res[i] = res[idx - i - 1];
        res[idx - i - 1] = t;
    }

    return res;
}