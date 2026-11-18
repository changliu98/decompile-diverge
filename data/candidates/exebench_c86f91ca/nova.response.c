void remove_dupc2(char *s) {
    int i = 0, j;
    while (1) {
        if (s[i] == '\0')
            break;
        if (s[i] == -1)
            continue;
        j = i + 1;
        while (1) {
            if (s[j] == '\0')
                break;
            if (s[i] == s[j])
                s[j] = -1;
            else
                j++;
        }
        i++;
    }
    j = 0;
    if (s[j] == '\0')
        return;
    while (1) {
        if (s[j] == -1)
            j++;
        else
            break;
    }
    i = j + 1;
    while (1) {
        if (s[i] == '\0')
            break;
        if (s[i] == -1)
            i++;
        else
            s[++j] = s[i++];
    }
    s[++j] = '\0';
}