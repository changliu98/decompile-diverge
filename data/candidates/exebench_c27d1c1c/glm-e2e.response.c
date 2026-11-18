void reverse(char *str) {
    if (str == 0) {
        return;
    }
    
    char *end = str;
    while (*end != '\0') {
        end++;
    }
    end--;
    
    while (str < end) {
        char temp = *end;
        *end = *str;
        end--;
        *str = temp;
        str++;
    }
}