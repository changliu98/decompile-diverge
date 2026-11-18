void reverse(char *str) {
    long len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    if (len > 0) {
        long left = 0;
        long right = len - 1;
        while (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}