char* func0(char* str) {
    char* tokens[100];
    int count = 0;
    char* token = strtok(str, " ");
    char* result = "";
    
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(tokens[i], token) == 0) {
                result = token;
                return result;
            }
        }
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }
    
    return result;
}