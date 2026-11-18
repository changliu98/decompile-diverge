#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** func0(const char* paren_string, int* group_count) {
    int length = strlen(paren_string);
    int level = 0;
    int capacity = 10;
    char** groups = malloc(capacity * sizeof(char*));
    char* buffer = malloc(length + 1);
    int buffer_index = 0;
    *group_count = 0;

    for (int i = 0; i < length; ++i) {
        char chr = paren_string[i];
        if (chr == '(') {
            level++;
            buffer[buffer_index++] = chr;
        } else if (chr == ')') {
            level--;
            buffer[buffer_index++] = chr;
            if (level == 0) {
                buffer[buffer_index] = '\0';
                groups[*group_count] = strdup(buffer);
                (*group_count)++;
                if (*group_count >= capacity) {
                    capacity *= 2;
                    groups = realloc(groups, capacity * sizeof(char*));
                }
                buffer_index = 0;
            }
        }
    }

    free(buffer);
    return groups;
}
