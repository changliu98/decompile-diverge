int func0(const char *s1, const char *s2) {
    char buf1[0x70];
    char buf2[0x70];
    int num1_num, num1_den, num2_num, num2_den;

    int i = 0;
    while (s1[i] != '/') {
        buf1[i] = s1[i];
        i++;
    }
    buf1[i] = '\0';
    num1_num = atoi(buf1);

    int j = 0;
    i++;
    while (s1[i] != '\0') {
        buf2[j] = s1[i];
        i++;
        j++;
    }
    buf2[j] = '\0';
    num1_den = atoi(buf2);

    i = 0;
    while (s2[i] != '/') {
        buf1[i] = s2[i];
        i++;
    }
    buf1[i] = '\0';
    num2_num = atoi(buf1);

    j = 0;
    i++;
    while (s2[i] != '\0') {
        buf2[j] = s2[i];
        i++;
        j++;
    }
    buf2[j] = '\0';
    num2_den = atoi(buf2);

    return (num1_num * num2_num) % (num1_den * num2_den) == 0;
}