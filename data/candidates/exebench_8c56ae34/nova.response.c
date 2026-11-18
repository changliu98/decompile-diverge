void Reverse(char *s) {
    int i = 0;
    int j = 0;
    char temp;

    while (s[j]!= '\0') {
        j++;
    }
    j--;
    if (s[j] == '\n') {
        j--;
    }
    while (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        j--;
        i++;
    }
}