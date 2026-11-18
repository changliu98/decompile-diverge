void sort(char *str) {
    for (int i = 0; str[i + 1] != '\0'; i++) {
        char val = str[i + 1];
        int j = i;
        
        while (j > -1 && str[j] > val) {
            str[j + 1] = str[j];
            j--;
        }
        
        str[j + 1] = val;
    }
}