char* func0(const char* param1, const char* param2, int* param3) {
    // The original program likely had a static array of strings, e.g.:
    // static const char* strings[] = { "str1", "str2", ... };
    // The assembly copies this array to a local buffer.
    char* strings[8];
    memcpy(strings, (void*)0x3d60, 0x40); // 8 pointers * 8 bytes = 64 bytes

    int idx1 = -1;
    int idx2 = -1;

    for (int i = 0; i < 8; i++) {
        if (strcmp(strings[i], param1) == 0) {
            idx1 = i;
        }
        if (strcmp(strings[i], param2) == 0) {
            idx2 = i;
        }
    }

    // If either string is not found, or they are the same string
    if (idx1 == -1 || idx2 == -1 || idx1 == idx2) {
        *param3 = 0;
        return NULL;
    }

    // Ensure idx1 is less than idx2
    if (idx1 > idx2) {
        int temp = idx1;
        idx1 = idx2;
        idx2 = temp;
    }

    // Calculate the number of strings strictly between them
    *param3 = idx2 - idx1 - 1;

    // If there are no strings in between
    if (*param3 <= 0) {
        *param3 = 0;
        return NULL;
    }

    // Allocate an array of string pointers for the in-between strings
    char** result = (char**)malloc(*param3 * sizeof(char*));

    // Copy the pointers of the strings between idx1 and idx2
    for (int i = idx1 + 1; i < idx2; i++) {
        result[i - idx1 - 1] = strings[i];
    }

    return (char*)result;
}