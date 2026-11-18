int func0(int num) {
    char num_str[12];
    char rev_str[12];
    int i, len;
    while (--num > 0) {
        sprintf(num_str, "%d", num);
        strcpy(rev_str, num_str);
        len = strlen(rev_str);
        for (i = 0; i < len / 2; i ++) {
            char temp = rev_str[i];
            rev_str[i] = rev_str[len - 1 - i];
            rev_str[len - 1 - i] = temp;
        }
        if (!strcmp(num_str, rev_str)) {
            return num;
        }
    }
    return 0;
}