int func0(char *str) {
    char *p = "aeiouAEIOU";
    int i = 0, j = 0;
    while (1) {
        if (j >= strlen(str))
            break;
        if (strchr(p, str[j])!= NULL)
            i++;
        else
            j++;
    }
    return i;
}