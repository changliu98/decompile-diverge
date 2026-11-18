void ceasar(char *str, char shift) {
    int i = 0;
    int j = 0;
    
    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] > 0x40 && str[i] < 0x5b) || (str[i] > 0x60 && str[i] < 0x7b)) {
            for (j = 0; j < shift; j++) {
                if (str[i] == 'Z') {
                    str[i] = 'A';
                    str[i]--;
                }
                if (str[i] == 'z') {
                    str[i] = 'a';
                    str[i]--;
                }
                str[i]++;
            }
        }
    }
}