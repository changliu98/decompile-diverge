char *func0(const char *input, char *output) {
    int out_idx = 0;
    int capitalize_next = 1;
    int in_idx = 0;

    while (input[in_idx] != '\0') {
        if (input[in_idx] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                output[out_idx++] = toupper(input[in_idx]);
                capitalize_next = 0;
            } else {
                output[out_idx++] = input[in_idx];
            }
        }
        in_idx++;
    }
    
    output[out_idx] = '\0';
    return output;
}