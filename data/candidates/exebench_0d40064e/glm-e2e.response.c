void _prtX16(long val, char *buf) {
    char str[9] = {0};
    int i = 1;
    const char *hex = "0123456789abcdef"; // located at 0x2025

    // Convert the 64-bit integer to an 8-character hex string
    while (i <= 8) {
        str[i] = hex[val & 0xf];
        val >>= 4;
        i++;
    }

    // Skip leading zeros
    i = 8;
    while (str[i] == '0') {
        i--;
    }

    // If the entire number was zero, keep the last '0'
    if (i == 0) {
        i++;
    }

    // Copy the characters to the output buffer
    while (i >= 0) {
        i--;
        *buf = str[i + 1];
        buf++;
    }
}