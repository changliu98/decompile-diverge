#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** func0(const char* s, int* count) {
    int capacity = 10;
    char** out = malloc(capacity * sizeof(char*));
    char* current = malloc(strlen(s) + 1);
    int word_count = 0;
    int current_length = 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] == ' ' || s[i] == ',') {
            if (current_length > 0) {
                current[current_length] = '\0';
                out[word_count++] = strdup(current);
                current_length = 0;

                if (word_count >= capacity) {
                    capacity *= 2;
                    out = realloc(out, capacity * sizeof(char*));
                }
            }
        } else {
            current[current_length++] = s[i];
        }
    }

    if (current_length > 0) {
        current[current_length] = '\0';
        out[word_count++] = strdup(current);
    }

    free(current);
    *count = word_count;
    return out;
}
