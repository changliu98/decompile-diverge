void decrypt(char *str, int shift) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-') {
            str[i] = ' ';
        } else {
            int char_val = str[i] - 'a';
            int new_val = (char_val + shift) % 26;
            if (new_val < 0) {
                new_val += 26;
            }
            str[i] = 'a' + new_val;
        }
    }
}