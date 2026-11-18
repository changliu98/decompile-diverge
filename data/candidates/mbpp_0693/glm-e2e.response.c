char *func0(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int space_flag = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            if (!space_flag) {
                result[j++] = ' ';
                space_flag = 1;
            }
        } else {
            result[j++] = str[i];
            space_flag = 0;
        }
        i++;
    }
    
    result[j] = '\0';
    
    return result;
}