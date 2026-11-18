char** func0(char** strings, int num_strings, const char* substr, int* match_count) {
    char** matches = NULL;
    int count = 0;
    
    for (int i = 0; i < num_strings; i++) {
        if (strstr(strings[i], substr) != NULL) {
            matches = (char**)realloc(matches, (count + 1) * sizeof(char*));
            matches[count] = strings[i];
            count++;
        }
    }
    
    *match_count = count;
    return matches;
}