void sort(char *s) {
    int i = 0;
    while (1) {
        if (s[i + 1] == '\0')
            return;
        int j = i + 1;
        int c = s[j];
        while (1) {
            if (s[j] > c)
                s[j + 1] = s[j];
            else
                break;
            j--;
        }
        s[j + 1] = c;
        i++;
    }
}