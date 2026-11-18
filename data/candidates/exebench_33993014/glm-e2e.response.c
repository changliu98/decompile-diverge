int LI_ltostr(char *str, long value) {
    int length = 1;
    
    if (value < 0) {
        length++;
        *str = '-';
        str++;
        value = -value;
    }
    
    char *end = str;
    
    while (value > 9) {
        *end = (char)((value % 10) + '0');
        end++;
        value /= 10;
    }
    
    *end = (char)(value + '0');
    end[1] = '\0';
    
    length += (int)(end - str);
    
    while (str < end) {
        char temp = *end;
        *end = *str;
        *str = temp;
        str++;
        end--;
    }
    
    return length;
}