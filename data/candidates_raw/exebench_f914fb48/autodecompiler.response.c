void lowerToUpper(char *str) {
    int index = 0;
    while(1)
    {
        if (*(str + index) == '\0') {
            break;
        }
        if (*(str + index) >= 'a' && *(str + index) <= 'z') {
            *(str + index) -= 32;
        }
        index++;
    }
}