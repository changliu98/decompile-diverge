static char *func0(char *s1, char *s2) {
    char *s1c = strdup(s1);
    char *s2c = strdup(s2);
    int i = 0;
    while (1) {
        if (s1c[i] == '\0')
            break;
        if (s1c[i] == ',')
            s1c[i] = '.';
        i++;
    }
    int j = 0;
    while (1) {
        if (s2c[j] == '\0')
            break;
        if (s2c[j] == ',')
            s2c[j] = '.';
        j++;
    }
    double d1 = atof(s1c);
    char *r;
    if (*s1!= '\0') {
        free(s1c);
        free(s2c);
        r = (char *)"-";
    } else if (d1 == atof(s2c)) {
        free(s1c);
        free(s2c);
        r = (char *)"=";
    } else if (d1 > atof(s2c)) {
        r = s1;
    } else {
        r = s2;
    }
    return r;
}