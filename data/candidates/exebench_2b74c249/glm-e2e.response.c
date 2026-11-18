int setsize(uint64_t total_size, int *size1, int *size2, int *size3) {
    int ret = 0;
    uint64_t s1 = 1024; // 0x400
    uint64_t s2 = 62;   // 0x3e
    uint64_t s3;
    
    // Initial division to find the third dimension size
    uint64_t divisor = s1 * s2;
    s3 = total_size / divisor;
    
    // If there is a remainder, increment s3 and adjust s2
    if (total_size % divisor != 0) {
        s3 += 1;
        divisor = s1 * s3;
        s2 = total_size / divisor;
        
        // If there is still a remainder, increment s2 and adjust s1
        if (total_size % divisor != 0) {
            s2 += 1;
            divisor = s3 * s2;
            s1 = total_size / divisor;
        }
    }
    
    // If the first dimension size became 0, return an error (-1)
    if (s1 == 0) {
        ret = -1;
    }
    
    // Dereference and assign the calculated sizes to the output pointers
    *size1 = (int)s1;
    *size2 = (int)s2;
    *size3 = (int)s3;
    
    return ret;
}