void cenitPolarCrypt(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; cenit[j] != '\0'; j++) {
            if (str[i] == cenit[j]) {
                str[i] = polar[j];
                break;
            }
        }
    }
}