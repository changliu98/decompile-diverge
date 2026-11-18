void intToString(int num, char *str) {
    int i = 0;
    int temp = num;
    
    // Handle the special case where the number is 0
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    // Calculate the number of digits in the number
    while (temp != 0) {
        temp /= 10;
        i++;
    }
    
    // Null-terminate the string
    str[i] = '\0';
    i--;
    
    temp = num;
    
    // Fill the string with digits from right to left
    while (i >= 0) {
        str[i] = (temp % 10) + '0';
        i--;
        temp /= 10;
    }
}