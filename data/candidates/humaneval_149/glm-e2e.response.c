char** func0(char** strings, int n, int* out_count) {
    *out_count = 0;
    
    // Filter strings with even lengths
    for (int i = 0; i < n; i++) {
        if (strlen(strings[i]) % 2 == 0) {
            strings[*out_count] = strings[i];
            (*out_count)++;
        }
    }
    
    // Sort the filtered strings using bubble sort
    for (int i = 0; i < *out_count - 1; i++) {
        for (int j = 0; j < *out_count - i - 1; j++) {
            size_t len1 = strlen(strings[j]);
            size_t len2 = strlen(strings[j + 1]);
            
            // Swap if len1 > len2, or if lengths are equal and strings[j] > strings[j+1]
            if (len1 > len2 || (len1 == len2 && strcmp(strings[j], strings[j + 1]) > 0)) {
                char* temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
    
    // Allocate a new array to store the result
    char** result = (char**)malloc(*out_count * sizeof(char*));
    for (int i = 0; i < *out_count; i++) {
        result[i] = strings[i];
    }
    
    return result;
}