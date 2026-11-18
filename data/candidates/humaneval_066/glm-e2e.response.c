int func0(char *str) {
    int sum = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            sum += str[i];
        }
        i++;
    }
    
    return sum;
}