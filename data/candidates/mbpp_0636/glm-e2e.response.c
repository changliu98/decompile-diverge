const char* func0(int a, int b, int c) {
    const char* result;
    if (a == c) {
        result = "Equal"; // Assuming the string at 0x2004 is "Equal"
    } else {
        result = "Not Equal"; // Assuming the string at 0x2008 is "Not Equal"
    }
    return result;
}