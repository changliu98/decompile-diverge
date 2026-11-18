char** func0(char* paren_string, int* group_count) {
    int level = 0;
    int length = strlen(paren_string);
    int capacity = 10;
    char** groups = malloc(sizeof(char*) * capacity);
    char* buffer = malloc(sizeof(char) * (length + 1));
    int buffer_index = 0;
    *group_count = 0;
    for (int i = 0; i < length; i++) {
        if (paren_string[i] == '(') {
            level++;
            buffer[buffer_index++] = '(';
        } else if (paren_string[i] == ')') {
            level--;
            buffer[buffer_index++] = ')';
            if (level == 0) {
                buffer[buffer_index] = '\0';
                groups[*group_count] = strdup(buffer);
                *group_count = *group_count + 1;
                if (*group_count >= capacity) {
                    capacity *= 2;
                    groups = realloc(groups, sizeof(char*) * capacity);
                }
                buffer_index = 0;
            }
        }
    }
    free(buffer);
    return groups;
}