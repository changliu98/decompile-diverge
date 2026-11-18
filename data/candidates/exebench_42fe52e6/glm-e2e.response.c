int itoa(char *buf, int num) {
    int len;
    
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        len = 2;
        return len;
    }
    
    int count = 0;
    int divisor = 1;
    int n = (num < 0) ? -num : num;
    
    // Calculate the number of digits and the maximum divisor
    while (n % divisor != n) {
        count++;
        divisor *= 10;
    }
    
    // Add an extra count for the negative sign
    if (num < 0) {
        count++;
    }
    
    divisor = 1;
    
    // Extract and place each digit in the buffer
    for (int i = count - 1; i >= 0; i--) {
        int rem = n;
        int q = (rem - (rem % divisor)) / divisor;
        buf[i] = (q % 10) + '0';
        divisor *= 10;
    }
    
    // Add the negative sign if necessary
    if (num < 0) {
        buf[0] = '-';
    }
    
    // Null-terminate the string
    buf[count] = '\0';
    len = count;
    
    return len;
}