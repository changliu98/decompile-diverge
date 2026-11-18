void func0(char *str1, char *str2) {
    int i = 0;
    int j = 0;
    
    while (str1[i] != '\0') {
        if (!isspace(str1[i])) {
            str2[j++] = str1[i];
        }
        i++;
    }
    
    str2[j] = '\0';
}