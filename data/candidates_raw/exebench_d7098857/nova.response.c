void func0(char *s, char ch) {
    char *t = s;
    int i = 0, j = 0;
    while (1) {
        if (*(t + j)!= 0) {
            if (*(t + j)!= ch) {
                *(s + i) = *(t + j);
                i++;
            }
        } else
            break;
        j++;
    }
    *(s + i) = 0;
}