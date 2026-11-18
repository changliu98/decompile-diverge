void oct_to_word(char *word, char oct) {
    if (word != NULL) {
        word[0] = (oct >> 6) & 0x03;
        word[1] = (oct >> 3) & 0x07;
        word[2] = oct & 0x07;

        for (char i = 0; i < 3; i++) {
            word[i] += '0';
        }
    }
}