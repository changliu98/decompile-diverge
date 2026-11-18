int func0(char *s) {
    int i, j, k, l, flag;
    l = strlen(s);
    while (s[0] =='') {
        s++;
        l--;
    }
    if (l < 2)
        return -1;
    if (s[0] == '+' || s[0] == '-') {
        flag = 1;
        for (i = 1; i < l; i++) {
            if (s[i] < '0' || s[i] > '9') {
                flag = 0;
                break;
            }
        }
    } else
        flag = 1;
    if (flag == 0)
        return 0;
    else
        return 1;
}