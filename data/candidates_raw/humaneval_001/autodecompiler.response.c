char** parse_paren_groups(char* input, int* n_groups) {
    int len = strlen(input);
    int level = 0;
    int capacity = 10;
    char** groups = malloc(capacity * sizeof(char*));
    char* buffer = malloc(len + 1);
    int buffer_index = 0;

    *n_groups = 0;

    for(int i = 0; i < len; i++) {
        char c = input[i];

        switch(c) {
            case '(':
                level++;
                buffer[buffer_index++] = c;
                break;
            case ')':
                level--;
                buffer[buffer_index++] = c;
                if(level == 0) {
                    buffer[buffer_index] = '\0';
                    groups[*n_groups] = strdup(buffer);

                    *n_groups += 1;
                    if(*n_groups >= capacity) {
                        capacity *= 2;
                        groups = realloc(groups, capacity * sizeof(char*));
                    }

                    buffer_index = 0;
                }
                break;
            default:
                break;
        }
    }

    free(buffer);

    return groups;
}