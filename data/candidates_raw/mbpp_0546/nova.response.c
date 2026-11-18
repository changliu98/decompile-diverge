int func0(char *str, char c) {
    int i, j, len, index;
    index = -1;
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == c) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        j = -1;
    } else {
        j = index + 1;
    }
    return j;
}