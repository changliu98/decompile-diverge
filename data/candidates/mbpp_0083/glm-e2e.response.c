char func0(const char *s) {
    int sum = 0;
    int i = 0;
    
    while (s[i] != '\0') {
        sum += s[i] - 'a' + 1;
        i++;
    }
    
    if (sum % 26 == 0) {
        return 'z';
    }
    
    return (sum % 26) + 'a' - 1;
}