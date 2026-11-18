char** func0(char** param1, int param2, char** param3, int param4) {
    int len1 = 0;
    int len2 = 0;
    int i;
    char** result;

    // Calculate total length of strings in param1
    for (i = 0; i < param2; i++) {
        len1 += strlen(param1[i]);
    }

    // Calculate total length of strings in param3
    for (i = 0; i < param4; i++) {
        len2 += strlen(param3[i]);
    }

    // Compare lengths and return the appropriate array
    if (len1 < len2) {
        result = param1;
    } else if (len1 > len2) {
        result = param3;
    } else {
        result = param1;
    }

    return result;
}