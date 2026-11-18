exact size might vary

char* func0(char* param1) {
    strcpy(result, param1);
    for (int i = 0; result[i] != '\0'; i++) {
        if (result[i] == ' ' || result[i] == ',' || result[i] == '.') {
            result[i] = ':';
        }
    }
    return result;
}