int func0(char *str1, char *str2) {
    int i;
    int count = 0;
    int len = strlen(str1);
    for (i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    if (count % 2 == 0) {
        return count / 2;
    } else {
        return -1;
    }
}