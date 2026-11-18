int dummyfunc(char s[]) {
    int i = 0;
    char c;
    while (1) {
        c = s[i];
        if (c!= '\0') {
            s[i] = toupper(c);
            i++;
        } else {
            break;
        }
    }
}