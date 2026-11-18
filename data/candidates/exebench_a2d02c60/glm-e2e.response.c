int ft_pn(char *str, int *status, int i) {
    while (1) {
        char c = str[i];
        int is_space = (c == ' ');
        
        if (!is_space) {
            int is_whitespace = (c >= 9 && c <= 13);
            is_space = is_whitespace;
        }
        
        if (!is_space) {
            break;
        }
        i++;
    }
    
    if (str[i] == 0) {
        *status = -3;
    }
    
    if (str[i] == '-') {
        *status = -2;
    }
    
    return i;
}