void decrypt(char string[], int shift) {
    int i = 0;

    while (string[i] != '\0') {
        if (string[i] == '-') {
            string[i] = ' ';
        }
        else {
            string[i] = (string[i] - 'a' + shift % 26) % 26 + 'a';
        }
        i++;
    }
}