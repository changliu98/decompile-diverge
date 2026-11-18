void set_nb(const char *str, char ch, int *count) {
    int i = 0;
    int j = 0;
    
    while (str[i] != '\0') {
        if (i == j) {
            if (str[i] == ch) {
                i++;
                j++;
            } else {
                if (str[j] == ch || str[j] == '\0') {
                    (*count)++;
                    i = j;
                } else {
                    j++;
                }
            }
        } else {
            if (str[j] == ch || str[j] == '\0') {
                (*count)++;
                i = j;
            } else {
                j++;
            }
        }
    }
}