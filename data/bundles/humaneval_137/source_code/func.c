#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* func0(const char* a, const char* b) {
    char *end;
    char *a_modified = strdup(a);
    char *b_modified = strdup(b);

    // Replace ',' with '.' if present for atof conversion
    for (int i = 0; a_modified[i]; ++i) if (a_modified[i] == ',') a_modified[i] = '.';
    for (int i = 0; b_modified[i]; ++i) if (b_modified[i] == ',') b_modified[i] = '.';

    double numa = strtod(a_modified, &end);
    if (*end) { free(a_modified); free(b_modified); return "Invalid input"; } // Not a valid number
    double numb = strtod(b_modified, &end);
    if (*end) { free(a_modified); free(b_modified); return "Invalid input"; } // Not a valid number

    free(a_modified);
    free(b_modified);

    if (numa == numb) return "None";
    return numa > numb ? (char*)a : (char*)b;
}
