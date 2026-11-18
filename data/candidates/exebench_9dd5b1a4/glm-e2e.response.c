int add_char_to_string(char *str, char c, unsigned int max_size) {
    if (str == NULL) {
        return 0;
    }

    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    // Check if there is space for the new character and the null terminator
    if (i >= (int)max_size - 1) {
        return 0;
    }

    str[i] = c;
    str[i + 1] = '\0';

    return 1;
}