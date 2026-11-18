#include <string.h>
#include <stdlib.h>

char** filter_strings_by_substring(char** strings, int size, const char* substring, int* out_size) {
    char** filtered_strings = NULL;
    int count = 0;

    for (int i = 0; i < size; ++i) {
        // If the substring is found within the current string
        if (strstr(strings[i], substring) != NULL) {
            // Allocate memory for the new pointer in the filtered list
            char** temp = (char**)realloc(filtered_strings, sizeof(char*) * (count + 1));
            if (temp == NULL) {
                // Handle allocation failure gracefully
                *out_size = count;
                return filtered_strings; 
            }
            filtered_strings = temp;
            
            // Add the string pointer to the list and increment the count
            filtered_strings[count++] = strings[i];
        }
    }

    *out_size = count;
    return filtered_strings;
}