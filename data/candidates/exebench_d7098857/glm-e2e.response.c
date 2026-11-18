void misc_str_remove_symbol(char *str, char symbol) {
    int write_idx = 0;
    int read_idx = 0;
    
    while (str[read_idx] != '\0') {
        if (str[read_idx] != symbol) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    
    str[write_idx] = '\0';
}