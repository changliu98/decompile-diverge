void toUpperCase(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        char c = 'a'; // 0x61
        while (c <= 'z') { // 0x7a
            if (str[i] == c) {
                str[i] -= 0x20; // Convert to uppercase
            }
            c++;
        }
        i++;
    }
}