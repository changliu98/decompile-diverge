void func0(const char *input, char *output) {
    int space_count = 0;
    int out_idx = 0;
    
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            space_count++;
        } else {
            if (space_count == 1) {
                output[out_idx++] = '_';
            }
            if (space_count == 2) {
                output[out_idx++] = '_';
                output[out_idx++] = '_';
            }
            if (space_count > 2) {
                output[out_idx++] = '-';
            }
            space_count = 0;
            output[out_idx++] = input[i];
        }
    }
    
    // Handle trailing spaces at the end of the string
    if (space_count == 1) {
        output[out_idx++] = '_';
    }
    if (space_count == 2) {
        output[out_idx++] = '_';
        output[out_idx++] = '_';
    }
    if (space_count > 2) {
        output[out_idx++] = '-';
    }
    
    output[out_idx] = '\0';
}