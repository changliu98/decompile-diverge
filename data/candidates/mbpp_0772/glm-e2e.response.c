char* func0(const char* input_str, int target_len) {
    char buffer[0x400];
    char* result;
    char* token;
    size_t len;

    // Copy the input string into a local buffer to safely tokenize it
    strncpy(buffer, input_str, 0x3e8);

    // Allocate memory for the resulting string
    result = (char*)malloc(strlen(input_str) + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    result[0] = '\0';

    // Tokenize the string by spaces
    token = strtok(buffer, " ");
    while (token != NULL) {
        // Append the token if its length does not match target_len
        if (strlen(token) != target_len) {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }

    // Remove trailing space if present
    len = strlen(result);
    if (len > 0 && result[len - 1] == ' ') {
        result[len - 1] = '\0';
    }

    return result;
}