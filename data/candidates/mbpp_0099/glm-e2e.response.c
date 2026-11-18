char *func0(int n) {
    int len = 0;
    
    // Convert n to binary string (in reverse order)
    while (n > 0) {
        binary[len] = (n % 2) + '0';
        len++;
        n = n / 2;
    }
    binary[len] = '\0';
    
    // Reverse the string in-place
    int i = 0;
    int j = len - 1;
    while (i < j) {
        char temp = binary[i];
        binary[i] = binary[j];
        binary[j] = temp;
        i++;
        j--;
    }
    
    return binary;
}