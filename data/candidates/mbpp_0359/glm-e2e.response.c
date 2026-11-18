const char* func0(int a, int b, int c) {
    const char* result;
    
    // eax = b * 2 * b
    // ecx = a * 9 * c
    if (b * 2 * b == a * 9 * c) {
        result = "Yes"; // Address 0x2004
    } else {
        result = "No";  // Address 0x2008
    }
    
    return result;
}