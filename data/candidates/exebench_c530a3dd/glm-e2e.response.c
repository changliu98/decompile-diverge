int str_copy(char *dst, char *src) {
    int count = 0;
    
    while (1) {
        // Iteration 1
        *dst = *src;
        if (*dst == '\0') return count;
        dst++; src++; count++;
        
        // Iteration 2
        *dst = *src;
        if (*dst == '\0') return count;
        dst++; src++; count++;
        
        // Iteration 3
        *dst = *src;
        if (*dst == '\0') return count;
        dst++; src++; count++;
        
        // Iteration 4
        *dst = *src;
        if (*dst == '\0') return count;
        dst++; src++; count++;
        
        // Iteration 5
        *dst = *src;
        if (*dst == '\0') return count;
        dst++; src++; count++;
    }
}